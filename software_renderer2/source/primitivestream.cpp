#include "primitivestream.h"
#include <cassert>

PrimitiveStream::PrimitiveStream(PrimitiveType type,u8 uvDimension)
 : type_(type)
 , uvDimension_(uvDimension) {
}

PrimitiveStream::~PrimitiveStream() {
}

PrimitiveType PrimitiveStream::primitiveType() const {
  return type_;
}

u32 PrimitiveStream::primitiveNum() const {
  int ret=0;
  switch(type_) {
    case PrimitiveType::TriangleList:
      ret=indexNum()/3;
    break;
    default:
      assert(false&&"Unknown primitive type in PrimitiveStream!");
    break;
  }
  return ret;
}

u32 PrimitiveStream::indexNum() const {
  return indexStream_.size();
}

u32 PrimitiveStream::vertexNum() const {
  return xyzwStream_.size();
}

u8 PrimitiveStream::uvDimension() const {
  return uvDimension_;
}

PrimitiveStream::INDEX_t& PrimitiveStream::indexAt(u32 idx) {
  return const_cast<PrimitiveStream::INDEX_t&>(
          const_cast<const PrimitiveStream*>(this)->indexAt(idx));
}

const PrimitiveStream::INDEX_t& PrimitiveStream::indexAt(u32 idx) const {
  return indexStream_[idx];
}

PrimitiveStream::XYZW_t& PrimitiveStream::xyzwAt(u32 idx) {
  return const_cast<PrimitiveStream::XYZW_t&>(
    const_cast<const PrimitiveStream*>(this)->xyzwAt(idx));
}

const PrimitiveStream::XYZW_t& PrimitiveStream::xyzwAt(u32 idx) const {
  return xyzwStream_[idx];
}

PrimitiveStream::UV_t& PrimitiveStream::uvAt(u32 idx) {
  return const_cast<PrimitiveStream::UV_t&>(
    const_cast<const PrimitiveStream*>(this)->uvAt(idx));
}

const PrimitiveStream::UV_t& PrimitiveStream::uvAt(u32 idx) const {
  return uvStream_[idx];
}

u32 PrimitiveStream::addPrimitive(INDEX_t idx0,INDEX_t idx1,INDEX_t idx2) {
  assert(vertexNum()>idx0);
  assert(vertexNum()>idx1);
  assert(vertexNum()>idx2);

  indexStream_.push_back(idx0);
  indexStream_.push_back(idx1);
  indexStream_.push_back(idx2);

  return primitiveNum()-1;
}

u32 PrimitiveStream::addVertex(const Vec4& xyzw,const UV_t& uv) {
  xyzwStream_.push_back(xyzw);
  uvStream_.push_back(uv);

  return vertexNum()-1;
}

PrimitiveStream* PrimitiveStream::clone() const {
  PrimitiveStream* cloned=new PrimitiveStream(type_,uvDimension_);
  cloned->xyzwStream_  = xyzwStream_;
  cloned->uvStream_    = uvStream_;
  cloned->indexStream_ = indexStream_;

  return cloned;
}