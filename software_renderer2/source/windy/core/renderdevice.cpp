#include "windy/core/renderdevice.h"
#include "windy/core/mainwindowwin32.h"
#include "windy/core/framebuffer.h"

#include <wrl/client.h>

namespace windy {
struct RenderDevice::Impl {
  std::unique_ptr<FrameBuffer>  frameBuffer;
  HDC           mainWindowDC;
  HDC           memoryDC;
  IMainWindow*  mainWindow;
};

RenderDevice::RenderDevice(IMainWindow& window,
                           u32 frame_width,
                           u32 frame_height) :
  impl_(new Impl) 
{
  impl_->mainWindow=&window;
  HWND nativeHandle=static_cast<MainWindowWin32&>(window).nativeHandle();

  HDC mainWindowDC=GetDC(nativeHandle);
  impl_->mainWindowDC=mainWindowDC;
  HDC memoryDC=CreateCompatibleDC(mainWindowDC);
  impl_->memoryDC=memoryDC;

  BITMAPINFO bitmapInfo;
  memset(&bitmapInfo,0,sizeof(BITMAPINFO));
  BITMAPINFOHEADER* header=&bitmapInfo.bmiHeader;

  constexpr u32 kBytesPerComponent=1;
  constexpr u32 kBytesPerPixel=kBytesPerComponent*4;
  void* rawPixels=nullptr;
  header->biSize=sizeof(BITMAPINFOHEADER);
  header->biWidth=frame_width;
  header->biHeight=frame_height;
  header->biPlanes=1;
  header->biBitCount=kBytesPerPixel;
  header->biCompression=BI_RGB;
  header->biSizeImage=frame_width*frame_height*kBytesPerPixel;
  HBITMAP hbmp=CreateDIBSection(memoryDC,
                                &bitmapInfo,
                                DIB_RGB_COLORS,
                                &rawPixels,
                                NULL,
                                NULL);
  SelectObject(memoryDC,hbmp);
}

RenderDevice::~RenderDevice() {
  DeleteDC(impl_->memoryDC);
  ReleaseDC(static_cast<MainWindowWin32*>(impl_->mainWindow)->nativeHandle(),
            impl_->mainWindowDC);
}

void RenderDevice::present() {
  StretchBlt(impl_->mainWindowDC,
             0,
             0,
             640,
             480,
             impl_->memoryDC,
             0,
             0,
             640,
             480,
             BLACKNESS);
}
}