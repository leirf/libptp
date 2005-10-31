/* properties.c
 *
 * Copyright (C) 2005 Mariusz Woloszyn <emsi@ipartners.pl>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <config.h>

#include "ptp.h"
#include <string.h>
#include <stdio.h>



#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif
int
ptp_prop_issupported(PTPParams* params, uint16_t property)
{
	int i=0;

	for (;i<params->deviceinfo.DevicePropertiesSupported_len;i++) {
		if (params->deviceinfo.DevicePropertiesSupported[i]==property)
			return 1;
	}
	return 0;
}

/* return ptp property name */

const char*
ptp_prop_getname(PTPParams* params, uint16_t dpc)
{
	int i;
	/* Device Property descriptions */
	static struct {
		uint16_t dpc;
		const char *txt;
	} ptp_device_properties[] = {
		{PTP_DPC_Undefined,		N_("PTP Undefined Property")},
		{PTP_DPC_BatteryLevel,		N_("Battery Level")},
		{PTP_DPC_FunctionalMode,	N_("Functional Mode")},
		{PTP_DPC_ImageSize,		N_("Image Size")},
		{PTP_DPC_CompressionSetting,	N_("Compression Setting")},
		{PTP_DPC_WhiteBalance,		N_("White Balance")},
		{PTP_DPC_RGBGain,		N_("RGB Gain")},
		{PTP_DPC_FNumber,		N_("F-Number")},
		{PTP_DPC_FocalLength,		N_("Focal Length")},
		{PTP_DPC_FocusDistance,		N_("Focus Distance")},
		{PTP_DPC_FocusMode,		N_("Focus Mode")},
		{PTP_DPC_ExposureMeteringMode,	N_("Exposure Metering Mode")},
		{PTP_DPC_FlashMode,		N_("Flash Mode")},
		{PTP_DPC_ExposureTime,		N_("Exposure Time")},
		{PTP_DPC_ExposureProgramMode,	N_("Exposure Program Mode")},
		{PTP_DPC_ExposureIndex,
					N_("Exposure Index (film speed ISO)")},
		{PTP_DPC_ExposureBiasCompensation,
					N_("Exposure Bias Compensation")},
		{PTP_DPC_DateTime,		N_("Date Time")},
		{PTP_DPC_CaptureDelay,		N_("Pre-Capture Delay")},
		{PTP_DPC_StillCaptureMode,	N_("Still Capture Mode")},
		{PTP_DPC_Contrast,		N_("Contrast")},
		{PTP_DPC_Sharpness,		N_("Sharpness")},
		{PTP_DPC_DigitalZoom,		N_("Digital Zoom")},
		{PTP_DPC_EffectMode,		N_("Effect Mode")},
		{PTP_DPC_BurstNumber,		N_("Burst Number")},
		{PTP_DPC_BurstInterval,		N_("Burst Interval")},
		{PTP_DPC_TimelapseNumber,	N_("Timelapse Number")},
		{PTP_DPC_TimelapseInterval,	N_("Timelapse Interval")},
		{PTP_DPC_FocusMeteringMode,	N_("Focus Metering Mode")},
		{PTP_DPC_UploadURL,		N_("Upload URL")},
		{PTP_DPC_Artist,		N_("Artist")},
		{PTP_DPC_CopyrightInfo,		N_("Copyright Info")},
		{0,NULL}
	};
	static struct {
		uint16_t dpc;
		const char *txt;
	} ptp_device_properties_EK[] = {
		{PTP_DPC_EK_ColorTemperature,	N_("EK Color Temperature")},
		{PTP_DPC_EK_DateTimeStampFormat,
					N_("EK Date Time Stamp Format")},
		{PTP_DPC_EK_BeepMode,		N_("EK Beep Mode")},
		{PTP_DPC_EK_VideoOut,		N_("EK Video Out")},
		{PTP_DPC_EK_PowerSaving,	N_("EK Power Saving")},
		{PTP_DPC_EK_UI_Language,	N_("EK UI Language")},
		{0,NULL}
	};

	static struct {
		uint16_t dpc;
		const char *txt;
	} ptp_device_properties_CANON[] = {
		{PTP_DPC_CANON_BeepMode,	N_("CANON Beep Mode")},
		{PTP_DPC_CANON_UnixTime,	N_("CANON Time measured in"
						" secondssince 01-01-1970")},
		{PTP_DPC_CANON_FlashMemory,
					N_("CANON Flash Card Capacity")},
		{PTP_DPC_CANON_CameraModel,	N_("CANON Camera Model")},
		{0,NULL}
	};
/* Nikon Codes added by Corey Manders and Mehreen Chaudary */
	static struct {
		uint16_t dpc;
		const char *txt;
	} ptp_device_properties_NIKON[] = {
		{PTP_DPC_NIKON_ShootingBank,	N_("NIKON Shooting Bank")},
		{PTP_DPC_NIKON_ShootingBankNameA, N_("NIKON Shooting Bank Name A")},
		{PTP_DPC_NIKON_ShootingBankNameB, N_("NIKON Shooting Bank Name B")},
		{PTP_DPC_NIKON_ShootingBankNameC, N_("NIKON Shooting Bank Name C")},
		{PTP_DPC_NIKON_ShootingBankNameD, N_("NIKON Shooting Bank Name D")},
		{PTP_DPC_NIKON_RawCompression,	N_("NIKON Raw Compression")},
		{PTP_DPC_NIKON_WhiteBalanceAutoBias, N_("NIKON White Balance Auto Bias")},
		{PTP_DPC_NIKON_WhiteBalanceTungstenBias, N_("NIKON White Balance Tungsten Bias")},
		{PTP_DPC_NIKON_WhiteBalanceFlourescentBias, N_("NIKON White Balance Flourescent Bias")},
		{PTP_DPC_NIKON_WhiteBalanceDaylightBias, N_("NIKON White Balance Daylight Bias")},
		{PTP_DPC_NIKON_WhiteBalanceFlashBias, N_("NIKON White Balance Flash Bias")},
		{PTP_DPC_NIKON_WhiteBalanceCloudyBias, N_("NIKON White Balance Cloudy Bias")},
		{PTP_DPC_NIKON_WhiteBalanceShadeBias, N_("NIKON White Balance Shade Bias")},
		{PTP_DPC_NIKON_WhiteBalanceColourTemperature, N_("NIKON White Balance Colour Temperature")},
		{PTP_DPC_NIKON_ImageSharpening, N_("NIKON Image Sharpening")},
		{PTP_DPC_NIKON_ToneCompensation, N_("NIKON Tone Compensation")},
		{PTP_DPC_NIKON_ColourMode,	N_("NIKON Colour Mode")},
		{PTP_DPC_NIKON_HueAdjustment,	N_("NIKON Hue Adjustment")},
		{PTP_DPC_NIKON_NonCPULensDataFocalLength, N_("NIKON Non CPU Lens Data Focal Length")},
		{PTP_DPC_NIKON_NonCPULensDataMaximumAperture, N_("NIKON Non CPU Lens Data Maximum Aperture")},
		{PTP_DPC_NIKON_CSMMenuBankSelect, N_("NIKON CSM Menu Bank Select")},
		{PTP_DPC_NIKON_MenuBankNameA,	N_("NIKON Menu Bank Name A")},
		{PTP_DPC_NIKON_MenuBankNameB,	N_("NIKON Menu Bank Name B")},	
		{PTP_DPC_NIKON_MenuBankNameC,	N_("NIKON Menu Bank Name C")},
		{PTP_DPC_NIKON_MenuBankNameD,	N_("NIKON Menu Bank Name D")},
		{PTP_DPC_NIKON_A1AFCModePriority, N_("NIKON (A1) AFC Mode Priority")},
		{PTP_DPC_NIKON_A2AFSModePriority, N_("NIKON (A2) AFS Mode Priority")},
		{PTP_DPC_NIKON_A3GroupDynamicAF, N_("NIKON (A3) Group Dynamic AF")},
		{PTP_DPC_NIKON_A4AFActivation,	N_("NIKON (A4) AF Activation")},	
		{PTP_DPC_NIKON_A5FocusAreaIllumManualFocus, N_("NIKON (A5) Focus Area Illum Manual Focus")},
		{PTP_DPC_NIKON_FocusAreaIllumContinuous, N_("NIKON Focus Area Illum Continuous")},
		{PTP_DPC_NIKON_FocusAreaIllumWhenSelected, N_("NIKON Focus Area Illum When Selected")},
		{PTP_DPC_NIKON_A6FocusArea,	N_("NIKON (A6) Focus Area")},
		{PTP_DPC_NIKON_A7VerticalAFON, N_("NIKON (A7) Vertical AF ON")},
		{PTP_DPC_NIKON_B1ISOAuto,	N_("NIKON (B1) ISO Auto")},
		{PTP_DPC_NIKON_B2ISOStep,	N_("NIKON (B2) ISO Step")},
/*		{PTP_DPC_NIKON_B3EVStep,	N_("NIKON (B3) EV Step")}, */
		{PTP_DPC_NIKON_B4ExposureCompEv, N_("NIKON (B4) Exposure Comp Ev")},
		{PTP_DPC_NIKON_ExposureCompensation, N_("NIKON Exposure Compensation")},
		{PTP_DPC_NIKON_CenterWeightArea, N_("NIKON Center Weighted Area")},
		{PTP_DPC_NIKON_C1AELock,	N_("NIKON (C1) AE Lock Mode")},
		{PTP_DPC_NIKON_C2AELAFL,	N_("NIKON (C2) AE-L/AF-L Mode")},
		{PTP_DPC_NIKON_C3AutoMeterOff, N_("NIKON (C3) Auto Meter Off")},
		{PTP_DPC_NIKON_C4SelfTimer,	N_("NIKON (C4) Self Timer")},	
		{PTP_DPC_NIKON_C5MonitorOff,	N_("NIKON (C5) Monitor Off")},
		{PTP_DPC_NIKON_D1ShootingSpeed, N_("NIKON (D1) Shooting Speed")},
		{PTP_DPC_NIKON_D2MaximumShots, N_("NIKON (D2) Maximum Shots")},
		{PTP_DPC_NIKON_D3ExpDelayMode,	N_("NIKON (D3) ExpDelayMode")},	
		{PTP_DPC_NIKON_LongExposureNoiseReduction, N_("NIKON Long Exposure Noise Reduction")},
		{PTP_DPC_NIKON_D5FileNumberSequence, N_("NIKON (D5) File Number Sequence")},
		{PTP_DPC_NIKON_D6ControlPanelFinderRearControl, N_("NIKON (D6) Control Panel Finder Rear Control")},
		{PTP_DPC_NIKON_ControlPanelFinderViewfinder, N_("NIKON Control Panel Finder Viewfinder")},
		{PTP_DPC_NIKON_D7Illumination,	N_("NIKON (D7) Illumination")},
		{PTP_DPC_NIKON_E1FlashSyncSpeed, N_("NIKON (E1) Flash Sync Speed")},
		{PTP_DPC_NIKON_E2FlashShutterSpeed, N_("NIKON (E2) Flash Shutter Speed")},
		{PTP_DPC_NIKON_E3AAFlashMode, N_("NIKON (E3) AA Flash Mode")},
		{PTP_DPC_NIKON_E4ModelingFlash,	N_("NIKON (E4) Modeling Flash")},
		{PTP_DPC_NIKON_E5AutoBracketSet, N_("NIKON (E5) Auto Bracket Set")},
		{PTP_DPC_NIKON_E6ManualModeBracketing, N_("NIKON (E6) Manual Mode Bracketing")},
		{PTP_DPC_NIKON_E7AutoBracketOrder, N_("NIKON (E7) Auto Bracket Order")},
		{PTP_DPC_NIKON_E8AutoBracketSelection, N_("NIKON (E8) Auto Bracket Selection")},
		{PTP_DPC_NIKON_F1CenterButtonShootingMode, N_("NIKON (F1) Center Button Shooting Mode")},
		{PTP_DPC_NIKON_CenterButtonPlaybackMode, N_("NIKON Center Button Playback Mode")},
		{PTP_DPC_NIKON_F2Multiselector, N_("NIKON (F2) Multiselector")},
		{PTP_DPC_NIKON_F3PhotoInfoPlayback, N_("NIKON (F3) PhotoInfoPlayback")},	
		{PTP_DPC_NIKON_F4AssignFuncButton, N_("NIKON (F4) Assign Function Button")},
		{PTP_DPC_NIKON_F5CustomizeCommDials, N_("NIKON (F5) Customize Comm Dials")},
		{PTP_DPC_NIKON_ChangeMainSub,	N_("NIKON Change Main Sub")},
		{PTP_DPC_NIKON_ApertureSetting, N_("NIKON Aperture Setting")},
		{PTP_DPC_NIKON_MenusAndPlayback, N_("NIKON Menus and Playback")},
		{PTP_DPC_NIKON_F6ButtonsAndDials, N_("NIKON (F6) Buttons and Dials")},
		{PTP_DPC_NIKON_F7NoCFCard,	N_("NIKON (F7) No CF Card")},
		{PTP_DPC_NIKON_AutoImageRotation, N_("NIKON Auto Image Rotation")},
		{PTP_DPC_NIKON_ExposureBracketing, N_("NIKON Exposure Bracketing")},
		{PTP_DPC_NIKON_ExposureBracketingIntervalDist, N_("NIKON Exposure Bracketing Interval Distance")},
		{PTP_DPC_NIKON_ExposureBracketingNumBracketPlace, N_("NIKON Exposure Bracketing Number Bracket Place")},
		{PTP_DPC_NIKON_AutofocusLCDTopMode2, N_("NIKON Autofocus LCD Top Mode 2")},
		{PTP_DPC_NIKON_AutofocusArea, N_("NIKON Autofocus Area selector")},
		{PTP_DPC_NIKON_LightMeter,	N_("NIKON Light Meter")},
		{PTP_DPC_NIKON_ExposureApertureLock, N_("NIKON Exposure Aperture Lock")},
		{PTP_DPC_NIKON_MaximumShots,	N_("NIKON Maximum Shots")},
                {PTP_DPC_NIKON_Beep, N_("NIKON AF Beep Mode")},
                {PTP_DPC_NIKON_AFC, N_("NIKON AF-C Set")},
                {PTP_DPC_NIKON_AFAssistOFF, N_("NIKON AF Assist Lamp")},
                {PTP_DPC_NIKON_PADVPMode, N_("NIKON Auto ISO P/A/DVP Setting")},
                {PTP_DPC_NIKON_ReviewOff, N_("NIKON Image Review")},
                {PTP_DPC_NIKON_GridDisplay, N_("NIKON Viewfinder Grid Display")},
                {PTP_DPC_NIKON_AFAreaIllumination, N_("NIKON AF Area Illumination")},
                {PTP_DPC_NIKON_FlashMode, N_("NIKON Flash Mode")},
                {PTP_DPC_NIKON_FLashCommanderMode, N_("NIKON Flash Commander Mode")},
                {PTP_DPC_NIKON_FlashSignOff, N_("NIKON Flash Sign")},
                {PTP_DPC_NIKON_GridDisplay, N_("NIKON Grid Display")},
                {PTP_DPC_NIKON_FlashModeManualPower, N_("NIKON Manual Flash Power")},
                {PTP_DPC_NIKON_FlashModeCommanderPower, N_("NIKON Commander Flash Power")},
                {PTP_DPC_NIKON_FlashExposureCompensation, N_("NIKON Flash Exposure Compensation")},
                {PTP_DPC_NIKON_RemoteTimeout, N_("NIKON Remote Timeout")},
                {PTP_DPC_NIKON_ImageCommentString, N_("NIKON Image Comment String")},
                {PTP_DPC_NIKON_FlashOpen, N_("NIKON Flash Open")},
                {PTP_DPC_NIKON_FlashCharged, N_("NIKON Flash Charged")},
                {PTP_DPC_NIKON_LensID, N_("NIKON Lens ID")},
                {PTP_DPC_NIKON_FocalLengthMin, N_("NIKON Min. Focal Length")},
                {PTP_DPC_NIKON_FocalLengthMax, N_("NIKON Max. Focal Length")},
                {PTP_DPC_NIKON_MaxApAtMinFocalLength, N_("NIKON Max. Aperture at Min. Focal Length")},
                {PTP_DPC_NIKON_MaxApAtMaxFocalLength, N_("NIKON Max. Aperture at Max. Focal Length")},
                {PTP_DPC_NIKON_LowLight, N_("NIKON Low Light")},
                {PTP_DPC_NIKON_ExtendedCSMMenu, N_("NIKON Extended CSM Menu")},
                {PTP_DPC_NIKON_OptimiseImage, N_("NIKON Optimise Image")},
                {PTP_DPC_NIKON_ImageCommentAttached, N_("NIKON Image Comment")},
                {PTP_DPC_NIKON_AutoExposureLock, N_("NIKON AE Lock")},
                {PTP_DPC_NIKON_AutoFocusLock, N_("NIKON AF Lock")},
                {PTP_DPC_NIKON_CameraOrientation, N_("NIKON Camera orientation")},
                {PTP_DPC_NIKON_FlashSignOFF, N_("NIKON Flash Sign Off")},
                {PTP_DPC_NIKON_EVStep, N_("NIKON EV Step")},

		{0,NULL}
	};

	for (i=0; ptp_device_properties[i].txt!=NULL; i++)
		if (ptp_device_properties[i].dpc==dpc)
			return (ptp_device_properties[i].txt);

	/*if (dpc|PTP_DPC_EXTENSION_MASK==PTP_DPC_EXTENSION)*/
	switch (params->deviceinfo.VendorExtensionID) {
		case PTP_VENDOR_EASTMAN_KODAK:
			for (i=0; ptp_device_properties_EK[i].txt!=NULL; i++)
				if (ptp_device_properties_EK[i].dpc==dpc)
					return (ptp_device_properties_EK[i].txt);
			break;

		case PTP_VENDOR_CANON:
			for (i=0; ptp_device_properties_CANON[i].txt!=NULL; i++)
				if (ptp_device_properties_CANON[i].dpc==dpc)
					return (ptp_device_properties_CANON[i].txt);
			break;
		case PTP_VENDOR_NIKON:
			for (i=0; ptp_device_properties_NIKON[i].txt!=NULL; i++)
				if (ptp_device_properties_NIKON[i].dpc==dpc)
					return (ptp_device_properties_NIKON[i].txt);
			break;
	

		}
	return NULL;
}


/* return property value description */
#define RETPROPDESC(desc)	{\
			for (i=0; desc[i].txt!=NULL; i++)	\
				if (desc[i].dpc==dpd->DevicePropertyCode && \
					!strcmp(desc[i].val,strval))\
					return (desc[i].txt);\
			}

static struct {
	uint16_t dpc;
	char *val;
	const char *txt;
} pd[] = {
	{PTP_DPC_WhiteBalance, "1", N_("Manual")},
	{PTP_DPC_WhiteBalance, "2", N_("Automatic")},
	{PTP_DPC_WhiteBalance, "3", N_("One-push Automatic")},
	{PTP_DPC_WhiteBalance, "4", N_("Daylight")},
	{PTP_DPC_WhiteBalance, "5", N_("Fluorescent")},
	{PTP_DPC_WhiteBalance, "6", N_("Tungsten")},
	{PTP_DPC_WhiteBalance, "7", N_("Flash")},
	{PTP_DPC_FocusMode, "1", N_("Manual")},
	{PTP_DPC_FocusMode, "2", N_("Automatic")},
	{PTP_DPC_FocusMode, "3", N_("Automatic Macro")},
	{PTP_DPC_ExposureMeteringMode, "1", N_("Manual")},
	{PTP_DPC_ExposureMeteringMode, "2", N_("Center-weighted")},
	{PTP_DPC_ExposureMeteringMode, "3", N_("Multi-spot")},
	{PTP_DPC_ExposureMeteringMode, "4", N_("Center-spot")},
	{PTP_DPC_FlashMode, "1", N_("Auto flash")},
	{PTP_DPC_FlashMode, "2", N_("Flash off")},
	{PTP_DPC_FlashMode, "3", N_("Fill flash")},
	{PTP_DPC_FlashMode, "4", N_("Red eye auto")},
	{PTP_DPC_FlashMode, "5", N_("Red eye fill")},
	{PTP_DPC_FlashMode, "6", N_("External flash")},
	{PTP_DPC_ExposureProgramMode, "1", N_("Manual")},
	{PTP_DPC_ExposureProgramMode, "2", N_("Automatic (P)")},
	{PTP_DPC_ExposureProgramMode, "3", N_("Aperture Priority")},
	{PTP_DPC_ExposureProgramMode, "4", N_("Shutter Priority")},
	{PTP_DPC_ExposureProgramMode, "5", N_("Program Creative")},
	{PTP_DPC_ExposureProgramMode, "6", N_("Program Action")},
	{PTP_DPC_ExposureProgramMode, "7", N_("Portrait")},
	{PTP_DPC_StillCaptureMode, "1", N_("Normal")},
	{PTP_DPC_StillCaptureMode, "2", N_("Burst")},
	{PTP_DPC_StillCaptureMode, "3", N_("Timelapse")},
	{0, NULL, NULL}
};

static struct {
	uint16_t dpc;
	char *val;
	const char *txt;
} pd_NIKONN[] = {
	{PTP_DPC_CompressionSetting, "0", N_("JPEG Basic")},
	{PTP_DPC_CompressionSetting, "1", N_("JPEG Normal")},
	{PTP_DPC_CompressionSetting, "2", N_("JPEG Fine")},
	{PTP_DPC_CompressionSetting, "4", N_("NEF RAW")},
	{PTP_DPC_CompressionSetting, "5", N_("NEF+JPEG Basic")},
	{PTP_DPC_WhiteBalance, "2", N_("Automatic")},
	{PTP_DPC_WhiteBalance, "4", N_("Direct Sunlight")},
	{PTP_DPC_WhiteBalance, "5", N_("Fluorescent")},
	{PTP_DPC_WhiteBalance, "6", N_("Incadescent")},
	{PTP_DPC_WhiteBalance, "7", N_("Flash")},
	{PTP_DPC_WhiteBalance, "32784", N_("Cloudy")},
	{PTP_DPC_WhiteBalance, "32785", N_("Shade")},
	{PTP_DPC_WhiteBalance, "32787", N_("Preset")},
	{PTP_DPC_FocusMode, "32784", N_("AF-S (single-servo)")},
	{PTP_DPC_FocusMode, "32785", N_("AF-C (continuous-servo)")},
	{PTP_DPC_FlashMode, "4", N_("Red-eye reduction")},
	{PTP_DPC_FlashMode, "32784", N_("Front-courtain")},
	{PTP_DPC_FlashMode, "32785", N_("Slow Sync")},
	{PTP_DPC_FlashMode, "32786", N_("(Slow) Rear-curtain")},
	{PTP_DPC_FlashMode, "32787", N_("Slow Sync with Red-eye")},
	{PTP_DPC_ExposureProgramMode, "32784", N_("Camera Auto")},
	{PTP_DPC_ExposureProgramMode, "32785", N_("Portrait")},
	{PTP_DPC_ExposureProgramMode, "32786", N_("Landscape")},
	{PTP_DPC_ExposureProgramMode, "32787", N_("Close Up")},
	{PTP_DPC_ExposureProgramMode, "32788", N_("Sports")},
	{PTP_DPC_ExposureProgramMode, "32789", N_("Night Portrait")},
	{PTP_DPC_ExposureProgramMode, "32790", N_("Night Landscape")},
	{PTP_DPC_StillCaptureMode, "1", N_("Single Frame")},
	{PTP_DPC_StillCaptureMode, "2", N_("Continuous")},
	{PTP_DPC_StillCaptureMode, "32785", N_("Self-timer")},
	{PTP_DPC_StillCaptureMode, "32787", N_("Remote")},
	{PTP_DPC_StillCaptureMode, "32788", N_("Delayed Remote")},
	{0, NULL, NULL}
};

const char*
ptp_prop_getdesc(PTPParams* params, PTPDevicePropDesc *dpd, void *val)
{
	int i;
	const char *strval;
	/* Device Property descriptions */
	strval=ptp_prop_tostr(params, dpd, val);

	switch (params->deviceinfo.VendorExtensionID) {
		case PTP_VENDOR_NIKON:
			RETPROPDESC(pd_NIKONN);
			break;
	}

	RETPROPDESC(pd);

	return NULL;
}

/**
 * ptp_prop_tostr:
 * params:	PTPParams*
 * 		PTPDevicePropDesc *dpd	- Device Property structure
 *		void *value		- if not null convert this value
 *					  (used internaty to convert
 *					   values other than current)
 *
 * Returns:	pointer to staticaly allocated buffer with property value
 *		representation as string
 *
 **/

#define SVALLEN		256
#define SVALRET() { \
			if (n>=SVALLEN) strval[SVALLEN]='\0'; \
			return strval;\
}

const char *
ptp_prop_tostr (PTPParams* params, PTPDevicePropDesc *dpd, void *val)
{
	static char strval[SVALLEN];
	int n;
	void *value=val==NULL?dpd->CurrentValue:val;

	memset(&strval, 0, SVALLEN);

	switch (dpd->DataType) {
		case PTP_DTC_INT8:
			n=snprintf(strval,SVALLEN,"%hhi",*(char*)value);
			SVALRET();
		case PTP_DTC_UINT8:
			n=snprintf(strval,SVALLEN,"%hhu",*(unsigned char*)value);
			SVALRET();
		case PTP_DTC_INT16:
			n=snprintf(strval,SVALLEN,"%hi",*(int16_t*)value);
			SVALRET();
		case PTP_DTC_UINT16:
			n=snprintf(strval,SVALLEN,"%hu",*(uint16_t*)value);
			SVALRET();
		case PTP_DTC_INT32:
			n=snprintf(strval,SVALLEN,"%li",(long int)*(int32_t*)value);
			SVALRET();
		case PTP_DTC_UINT32:
			n=snprintf(strval,SVALLEN,"%lu",(unsigned long)*(uint32_t*)value);
			SVALRET();
		case PTP_DTC_STR:
			n=snprintf(strval,SVALLEN,"\"%s\"",(char *)value);
			SVALRET();
	}
	return NULL;
}

