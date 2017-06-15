//@date:2017.6.14
//@author:yangjie82@gmail.com
//@brief:geometry primitive stream
#pragma once
//#include <memory>
#include <vector>
#include <valarray>
#include "base.h"
#include "primitivetype.h"
#include "vec4.h"

class PrimitiveStream {
 public:
  typedef u32                   INDEX_t;
  typedef std::vector<INDEX_t>  INDEXVec_t;
  typedef Vec4                  XYZW_t;
  typedef std::vector<Vec4>     XYZWVec_t;
  typedef std::valarray<f32>    UV_t;
  typedef std::vector<UV_t>     UVVec_t;

  explicit PrimitiveStream(PrimitiveType type,u8 uvDimension);
  virtual ~PrimitiveStream();
  PrimitiveType primitiveType() const;
  u32 primitiveNum() const;
  u32 indexNum() const;
  u32 vertexNum() const;
  u8 uvDimension() const;
  INDEX_t& indexAt(u32 idx);
  const INDEX_t& indexAt(u32 idx) const;
  XYZW_t& xyzwAt(u32 idx);
  const XYZW_t& xyzwAt(u32 idx) const;
  UV_t& uvAt(u32 idx);
  const UV_t& uvAt(u32 idx) const;
  u32 addPrimitive(INDEX_t idx0,INDEX_t idx1,INDEX_t idx2);
  u32 addVertex(const Vec4& xyzw,const UV_t& uv);

 private:
  PrimitiveType type_;
  u8            uvDimension_;
  INDEXVec_t    indexStream_;
  XYZWVec_t     xyzwStream_;
  UVVec_t       uvStream_;
};