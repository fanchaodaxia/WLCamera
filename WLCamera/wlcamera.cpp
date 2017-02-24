//Qt include
//#include <QDebug>

//Camera include
#include "wlcamera.h"
#include <pylon/PylonIncludes.h>
#include <pylon/usb/BaslerUsbInstantCamera.h>
#include <pylon/PylonGUI.h>

#include "../Samples/C++/include/SampleImageCreator.h"




using namespace Basler_UsbCameraParams;
using namespace Pylon;
using namespace std;
typedef Pylon::CBaslerUsbInstantCamera Camera_t;
// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 1;



WLCamera::WLCamera()
{
    PylonInitialize();//Camera initialization
    CDeviceInfo info;
    info.SetDeviceClass( Camera_t::DeviceClass());
    try
    {
        if (~info.IsModelNameAvailable())
            throw "The USB Camera is not connected";
        else
        {
            Camera_t camera( CTlFactory::GetInstance().CreateFirstDevice(info));
            camera.Open();
            // Camera Configuration
            //Pixel format
            //camera.PixelFormat.SetValue(PixelFormat_YCbCr422_8);
            // Reverse X/Reverse Y
            //camera.ReverseX.SetValue(false); // Disable x rotation
            //camera.ReverseY.SetValue(false); // Disable y rotation
            // Binning, it is needed to improve the display frequency
            //camera.BinningVertical.SetValue(1); // Disable vertical binning
            //camera.BinningHorizontal.SetValue(1); //Disable horizontal binning
            // Image ROI, default no ROI
            /*int64_t CameraWidthMax = camera.WidthMax.GetValue();
            int64_t CameraHeightmax = camera.HeightMax.GetValue();
            cout << "Camera dimension" << CameraWidthMax << "x" << CameraHeightmax << endl;
            camera.Width.SetValue(CameraWidthMax);
            camera.Height.SetValue(CameraHeightmax);
            camera.OffsetY.SetValue(0);
            camera.OffsetX.SetValue(0);*/
            // Black level
            // Gain
            /* if (IsWritable(camera.GainAuto))
             {
                 camera.GainAuto.FromString("On"); //set to AutoGain
             }*/
            // Light source preset
            // Balance white
            // Gamma
            // Hue/Saturation
            // Brightness / Contrast
            //PGI feature set
            // Defect pixel correction
            // Backlight compenstaion

            //camera.Gain.SetValue(50000);


            //camera.ExposureTime.SetValue(40000.0);
            cout << "using device" << camera.GetDeviceInfo().GetModelName() << endl;
            camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);
            CGrabResultPtr ptrGrabResult;
            CPylonImageWindow imageWindow;
            while (camera.IsGrabbing())
            {
                //wait for an iamge and then retrive it, a timeout of 5000ms is used
                camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
                if (ptrGrabResult->GrabSucceeded())
                {
                    cout << "Grab OK!" << endl;
                    CPylonImage image;
                    image.AttachGrabResultBuffer(ptrGrabResult); // attach grab result to a pylon image
                    //compute the iamge size
                    uint32_t imageWidth = image.GetWidth();
                    uint32_t imageHeight = image.GetHeight();
                    // creat the window and display the image
                    bool windowCreated = false;
                    if (!imageWindow.IsValid())
                    {
                        imageWindow.Create(1, 400, 400, imageWidth, imageHeight);
                        imageWindow.SetImage(image);
                        //imageWindow.Show();
                        cout << "image window is shown" << endl;
                    }
                    windowCreated = true;
                    imageWindow.Show();
                }
            }

            while (1)
            {
                // keep display the image

            }
        }
    }
    catch (char* msg)
    {
        cerr << "Camera is not connected" << endl;
        cerr << *msg << endl;
    }

}

WLCamera::~WLCamera()
{
    // Releases all pylon resources.
    PylonTerminate();

}
