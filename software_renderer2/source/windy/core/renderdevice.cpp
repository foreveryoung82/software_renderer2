#include <cassert>
#include <vector>

#include "windy/core/renderdevice.h"
#include "windy/core/mainwindowwin32.h"
#include "windy/core/framebuffer.h"
#include "windy/core/inputvertexstream.h"
#include "windy/core/inputvertex.h"
#include "windy/core/shadedvertex.h"
#include "windy/core/ivertexshader.h"
#include "windy/core/rasterizer.h"

#include <wrl/client.h>

namespace windy {
struct RenderDevice::Impl {
  HDC            mainWindowDC;
  HDC            memoryDC;
  IMainWindow*   mainWindow;
  IVertexShader* vertexShader;

  std::unique_ptr<FrameBuffer>  frameBuffer;
  Rasterizer                    rasterizer;
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

void RenderDevice::setVertexShader(IVertexShader& vertex_shader) {
  impl_->vertexShader=&vertex_shader;
}

void RenderDevice::drawTriangles(const InputVertexStream& input_stream,
                                 u32 triangles_num) {
  assert(impl_->vertexShader);

  std::vector<ShadedVertex> shadedVertices;
  shadedVertices.reserve(triangles_num*3);

  // vertex shading
  for (u32 triangleIndex=0;triangleIndex<triangles_num;++triangleIndex) {
    for (u32 pointIndex=0;pointIndex<3;++pointIndex) {
      const u32 vertexIndex=triangleIndex*3+pointIndex;
      InputVertex inputVertex=input_stream.vertexAt(vertexIndex);
      ShadedVertex shadedVertex=impl_->vertexShader->shade(inputVertex);
      shadedVertices.push_back(shadedVertex);
    }
  }

  // pixel shading
  for (u32 triangleIndex=0;triangleIndex<triangles_num;++triangleIndex) {
    impl_->rasterizer.drawTriangle(shadedVertices.data(),
                                   triangles_num,
                                   *impl_->frameBuffer);
  }
}

void RenderDevice::present() {
  std::unique_ptr<FrameBuffer>& frameBuffer = impl_->frameBuffer;
  IMainWindow* mainWindow                   = impl_->mainWindow;
  //frameBuffer->clear(Color {0,0,0,0});
  //frameBuffer->setPixel(0,0,Color {0,0,0xff,0xff});
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