#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <usb.h>

#include "ptp_usb.h"

struct usb_device *device;
int vendor, product;

PTPParams* ptp_params;
PTP_USB ptp_usb;

PTPResult
ptp_read (PTPReq* req, unsigned int size, void *data); 
PTPResult
ptp_write (PTPReq* req, unsigned int size, void *data); 
void error(char *x,...);


query (usb_dev_handle* handle) {
	PTPObjectHandles* ptp_objecthandles=malloc(sizeof(PTPObjectHandles));
	PTPObjectInfo** ptp_objectinfo;
	int ret;
	struct objectinfo** objinfoarray;

	ptp_params->io_write = ptp_write;
	ptp_params->io_read = ptp_read;
	ptp_params->ptp_error=error;
	ptp_params->io_data=&ptp_usb;
	ptp_params->id=1;

	ptp_usb.handle=handle;
	ptp_usb.ep=0x01;


// Open session number 1
	if (ptp_opensession(ptp_params, 1)==PTP_RC_OK) printf("INIT OK\n");
// getindex
	if (ptp_getobjecthandles(ptp_params, ptp_objecthandles)==PTP_RC_OK) 
		printf("GETINDEX OK\nArray of %i elements\n",ptp_objecthandles->n);
	if (ptp_getobjectsinfo(ptp_params, ptp_objecthandles, ptp_objectinfo)
		==PTP_RC_OK)
		printf("GETOBJECTINFO OK!\n");
// close
	if (ptp_closesession(ptp_params)==PTP_RC_OK) printf ("CLOSE OK\n");

}

usb_dev_handle* open_device(struct usb_device *device) {
	usb_dev_handle *handle;
	
	if (!(handle = usb_open(device))) {
		printf("open device failed!\n");
		return 0;
	}
	printf ("device opened!\n");
	return handle;
}



int scan_bus (struct usb_bus* bus) {
	struct usb_device* roottree = bus->devices;
	struct usb_device *device;

	for( device = roottree;device;device=device->next) {
		if ((device->descriptor.idVendor == vendor) &&
			(device->descriptor.idProduct == product)) {
			usb_dev_handle *device_handle;

			printf("found device %s on bus %s (idVendor 0x%x idProduct 0x%x)\n",
			device->filename, device->bus->dirname,
			device->descriptor.idVendor,
			device->descriptor.idProduct );
			// XXX
			if (device_handle=open_device(device)) {
				// XXX
				query(device_handle);
			}
		} else {
			printf ("No match!\n");
		}
	}
}

PTPResult
ptp_read (PTPReq* req, unsigned int size, void *data) 
{
	PTP_USB *usb;
	int ret;

	usb=(PTP_USB*)data;

	ret=usb_bulk_read(usb->handle, usb->ep, (char *)req,
		PTP_RESP_LEN, PTP_USB_TIMEOUT);

	if (ret<0) return PTP_ERROR;
	return PTP_OK;
}


PTPResult
ptp_write (PTPReq* req, unsigned int size, void *data) 
{
	PTP_USB *usb;
	int ret;

	usb=(PTP_USB*)data;

	ret=usb_bulk_write(usb->handle, usb->ep, (char *)req,
		PTP_REQ_LEN, PTP_USB_TIMEOUT);

	if (ret<0) return PTP_ERROR;
	return PTP_OK;
}

void error(char *x,...) {
	char mesg[4096];
	va_list ap;

	va_start(ap, x);
	vsnprintf(mesg,4095, x, ap);
	fprintf(stderr,"%s:\n",mesg);
	perror("");
	va_end(ap);
	fflush(NULL);
}


main (int argc, char** argv)  {
	struct usb_bus* bus;

	ptp_params=malloc(sizeof(PTPParams));


	usb_init();
	usb_find_busses();
	usb_find_devices();
	
	if (argc<2) {
		vendor=0x40a;
		product=0x500;
	} else {
		vendor=strtol(argv[1], NULL, 16);
		product=strtol(argv[2], NULL, 16);
	}

	for( bus = usb_busses; bus; bus = bus->next ) {
		printf("found bus %s\n", bus->dirname );
		scan_bus (bus);

	}
}
