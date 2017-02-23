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
    Camera_t camera( CTlFactory::GetInstance().CreateFirstDevice(info));
    camera.Open();
    //camera.Gain.SetValue(50000);
    if (IsWritable(camera.GainAuto))
    {
        camera.GainAuto.FromString("Off");
    }
    camera.Gain.SetValue((camera.Gain.GetMin() + camera.Gain.GetMax())/2 );
    camera.ExposureTime.SetValue(40000.0);
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

                cout << "Grab OK!" <<endl;
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

        while(1)
        {
           // keep display the image

        }
        // Releases all pylon resources.
        PylonTerminate();





}

WLCamera::~WLCamera()
{
    // Releases all pylon resources.
    PylonTerminate();

}
