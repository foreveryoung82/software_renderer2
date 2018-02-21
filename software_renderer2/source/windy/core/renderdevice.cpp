#include "windy/core/renderdevice.h"
#include "windy/core/mainwindowwin32.h"
#include "windy/core/framebuffer.h"

#include <wrl/client.h>

namespace windy {
struct RenderDevice::Impl {
  HDC           mainWindowDC;
  HDC           memoryDC;
  IMainWindow*  mainWindow;
  std::unique_ptr<FrameBuffer>  frameBuffer;
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
  constexpr u32 kBitPersPixel=kBytesPerPixel*8;
  void* rawPixels=nullptr;
  header->biSize=sizeof(BITMAPINFOHEADER);
  header->biWidth=frame_width;
  header->biHeight=frame_height;
  header->biPlanes=1;
  header->biBitCount=kBitPersPixel;
  header->biCompression=BI_RGB;
  header->biSizeImage=frame_width*frame_height*kBytesPerPixel;
  HBITMAP hbmp=CreateDIBSection(memoryDC,
                                &bitmapInfo,
                                DIB_RGB_COLORS,
                                &rawPixels,
                                NULL,
                                NULL);
  SelectObject(memoryDC,hbmp);

  impl_->frameBuffer.reset(new FrameBuffer(static_cast<u32*>(rawPixels),
                                                             frame_width,
                                                             frame_height,
                                                             frame_width*4));
}

RenderDevice::~RenderDevice() {
  DeleteDC(impl_->memoryDC);
  auto* windowWin32=static_cast<MainWindowWin32*>(impl_->mainWindow);
  HWND nativeHandle=windowWin32->nativeHandle();
  ReleaseDC(nativeHandle,impl_->mainWindowDC);
}

void RenderDevice::present() {
  std::unique_ptr<FrameBuffer>& frameBuffer = impl_->frameBuffer;
  IMainWindow* mainWindow                   = impl_->mainWindow;
  frameBuffer->clear(0x00000000);
  frameBuffer->setPixel(0,0,0xFF0000FF);
  StretchBlt(impl_->mainWindowDC,
             0, 
             0,
             mainWindow->width(),
             mainWindow->height(),
             impl_->memoryDC,
             0,
             0,
             frameBuffer->width(),
             frameBuffer->height(),
             SRCCOPY);
}
}