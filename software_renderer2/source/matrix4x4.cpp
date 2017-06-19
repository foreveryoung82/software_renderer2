#include "matrix4x4.h"
#include <cmath>
#include <cassert>
#include <algorithm>
#include "matrix3x3.h"
#include "quaternion.h"

Matrix4x4 Matrix4x4::make(Vec4 const& x,
                          Vec4 const& y,
                          Vec4 const& z,
                          Vec4 const& w) {
  Matrix4x4 matrix;
  std::copy(x.begin(),x.end(),&matrix.m[0][0]);
  std::copy(y.begin(),y.end(),&matrix.m[1][0]);
  std::copy(z.begin(),z.end(),&matrix.m[2][0]);
  std::copy(w.begin(),w.end(),&matrix.m[3][0]);
  return matrix;
}

Matrix4x4 Matrix4x4::makeIdentity() {
  return Matrix4x4::make(Vec4::kUnitX,
                         Vec4::kUnitY,
                         Vec4::kUnitZ,
                         Vec4::kUnitW);
}

Matrix4x4 Matrix4x4::makeAffine(Vec3 const& x,
                                Vec3 const& y,
                                Vec3 const& z,
                                Vec3 const& w) {
  Matrix4x4 matrix;
  std::copy(x.begin(),x.end(),&matrix.m[0][0]);
  std::copy(y.begin(),y.end(),&matrix.m[1][0]);
  std::copy(z.begin(),z.end(),&matrix.m[2][0]);
  std::copy(w.begin(),w.end(),&matrix.m[3][0]);
  matrix.m[0][3]=0;
  matrix.m[1][3]=0;
  matrix.m[2][3]=0;
  matrix.m[3][3]=1;
  return matrix;
}

Matrix4x4 Matrix4x4::makeTranslation(Vec3 const& t) {
  Matrix4x4 matrix=makeIdentity();
  std::copy(t.begin(),t.end(),&matrix.m[3][0]);
  return matrix;
}

Matrix4x4 Matrix4x4::makeScale(Vec3 const& s) {
  Matrix4x4 matrix=makeIdentity();
  matrix.m[0][0]=s.x;
  matrix.m[1][1]=s.y;
  matrix.m[2][2]=s.y;
  return matrix;  
}

Matrix4x4 Matrix4x4::makeRotation(f32 radian,Vec3 const& unitAxis) {
  const float c=std::cosf(radian);
  const float s=std::sinf(radian);
  const float r=1.f-c;
  const float u11=unitAxis[0]*unitAxis[0];
  const float u12=unitAxis[0]*unitAxis[1];
  const float u13=unitAxis[0]*unitAxis[2];
  const float u22=unitAxis[1]*unitAxis[1];
  const float u23=unitAxis[1]*unitAxis[2];
  const float u33=unitAxis[2]*unitAxis[2];

  Matrix4x4 matrix;
  matrix.m[0][0]=c+r*u11;
  matrix.m[0][1]=r*u12+s*unitAxis[2];
  matrix.m[0][2]=r*u13-s*unitAxis[1];
  matrix.m[0][3]=0;

  matrix.m[1][0]=r*u12-s*unitAxis[2];
  matrix.m[1][1]=c+r*u22;
  matrix.m[1][2]=r*u23+s*unitAxis[0];
  matrix.m[1][3]=0;

  matrix.m[2][0]=r*u13+s*unitAxis[1];
  matrix.m[2][1]=r*u23-s*unitAxis[0];
  matrix.m[2][2]=c+r*u33;
  matrix.m[2][3]=0;

  matrix.m[3][0]=0;
  matrix.m[3][1]=0;
  matrix.m[3][2]=0;
  matrix.m[3][3]=1;
  return matrix;   
}

Matrix4x4 Matrix4x4makeRotation(const Quaternion& q) {
  // R_q(p)=(2w*w-1)p+2(v*p)p+2w(vxp), * means dot, x means cross
  Matrix4x4 ret;
  const f32 x=q.x;
  const f32 y=q.y;
  const f32 z=q.z;
  const f32 w=q.w;
  ret.m[0][0]=2*w*w-1+2*x*x;
  ret.m[0][1]=2*x*y+2*w*z;
  ret.m[0][2]=2*x*z-2*w*y;
  ret.m[0][3]=0;
  ret.m[1][0]=2*x*y-2*w*z;
  ret.m[1][1]=2*w*w-1+2*y*y;
  ret.m[1][2]=2*y*z+2*w*x;
  ret.m[1][3]=0;
  ret.m[2][0]=2*x*z-2*w*y;
  ret.m[2][1]=2*y*z-2*w*x;
  ret.m[2][2]=2*w*w-1+2*z*z;
  ret.m[2][3]=0;
  ret.m[3][0]=0;
  ret.m[3][1]=0;
  ret.m[3][2]=0;
  ret.m[3][3]=1;
  return ret;
}

//Matrix4x4 Matrix4x4::makeXShear(f32 factor) {
//  Matrix4x4 matrix=makeIdentity();
//  matrix.m[1][0]=factor;
//  return matrix;     
//}
//
//Matrix4x4 Matrix4x4::makeYShear(f32 factor) {
//  Matrix4x4 matrix=makeIdentity();
//  matrix.m[0][1]=factor;
//  return matrix;    
//}
//
const f32* Matrix4x4::begin() const {
  return &m[0][0];
}

f32* Matrix4x4::begin() {
  return const_cast<f32*>(const_cast<const Matrix4x4*>(this)->begin());
}

const f32* Matrix4x4::end() const {
  const int num=4;
  return (begin()+num*num);
}

f32* Matrix4x4::end() {
  return const_cast<f32*>(const_cast<const Matrix4x4*>(this)->end());
}

bool Matrix4x4::operator==(Matrix4x4 const& rhs) const {
  const bool ret=std::equal(begin(),end(),rhs.begin());
  return ret;
}

Matrix4x4 Matrix4x4::operator+(Matrix4x4 const& rhs) const {
  Matrix4x4 ret;
  std::transform(begin(),end(),rhs.begin(),ret.begin(),
    [](u8 a,u8 b)->u8{return a+b;});
  return ret;
}

Matrix4x4& Matrix4x4::operator+=(Matrix4x4 const& rhs) {
  std::transform(begin(),end(),rhs.begin(),begin(),
    [](u8 a,u8 b)->u8{return a+b;});
  return *this;
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4 const& rhs) const {
  Matrix4x4 ret;
  std::transform(begin(),end(),rhs.begin(),ret.begin(),
    [](u8 a,u8 b)->u8{return a-b;});
  return ret;
}

Matrix4x4& Matrix4x4::operator-=(Matrix4x4 const& rhs) {
  std::transform(begin(),end(),rhs.begin(),begin(),
    [](u8 a,u8 b)->u8{return a-b;});
  return *this;
}

Matrix4x4 Matrix4x4::operator-() const {
  Matrix4x4 ret;
  std::transform(begin(),end(),ret.begin(),[](u8 a)->u8{return -a;});
  return ret;
}

Matrix4x4 Matrix4x4::operator*(f32 factor) const {
  Matrix4x4 ret;
  std::transform(begin(),end(),ret.begin(),
    [factor](f32 v)->f32{return v*factor;});
  return ret;
}

Matrix4x4& Matrix4x4::operator*=(f32 factor) {
  std::transform(begin(),end(),begin(),
    [factor](f32 v)->f32{return v*factor;});
  return *this;  
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 const& rhs) const {
  Matrix4x4 ret;
  const int num=4;
  for (int c=0;c<num;++c) {
    for (int r=0;r<num;++r) {
      ret.m[c][r]=m[0][r]*rhs.m[c][0]+
                  m[1][r]*rhs.m[c][1]+
                  m[2][r]*rhs.m[c][2]+
                  m[3][r]*rhs.m[c][3];
    }
  }
  return ret;
}

Matrix4x4& Matrix4x4::operator*=(Matrix4x4 const& rhs) {
  Matrix4x4 t=*this*rhs;
  *this=t;
  return *this;
}

Vec4 Matrix4x4::operator*(Vec4 const& rhs) const {
  Vec4 ret;
  const int num=4;
  for (int r=0;r<num;++r) {
    ret.m[r]=m[0][r]*rhs.m[0]+
             m[1][r]*rhs.m[1]+
             m[2][r]*rhs.m[2]+
             m[3][r]*rhs.m[3];
  }
  return ret;  
}

Vec3 Matrix4x4::transformVector(Vec3 const& v) const {
  Vec4 v4=Vec4::make(v.x,v.y,v.z,0);
  Vec4 ret=*this*v4;
  return Vec3::make(ret);
}

Vec3 Matrix4x4::transformPoint(Vec3 const& p) const {
  Vec4 v3=Vec4::make(p.x,p.y,p.z,1);
  Vec4 ret=*this*v3;
  ret*=1.f/ret.w;
  return Vec3::make(ret);
}

Matrix4x4 Matrix4x4::inverse() const {
  Matrix4x4 ret;
  const int num=4;
  const f32 inverse_determinant=1.f/determinant();
  for (int i=0;i<num;++i) {
    for (int j=0;j<num;++j) {
      ret.m[i][j]=inverse_determinant*algebraicCofactor(i,j);
    }
  }
  return ret;
}

Matrix4x4 Matrix4x4::transpose() const {
  Matrix4x4 ret;
  const int num=4;
  for (int c=0;c<num;++c) {
    for (int r=0;r<num;++r) {
      ret.m[c][r]=m[r][c];
    }
  }
  return ret;
}

f32 Matrix4x4::determinant() const {
  // Laplace expansion by 1th column
  f32 ret=m[0][0]*cofactor(0,0)+
          -m[0][1]*cofactor(1,0)+
          m[0][2]*cofactor(2,0)+
          -m[0][3]*cofactor(3,0);
  return ret;
}

f32 Matrix4x4::cofactor(u8 r,u8 c) const {
  Matrix3x3 m3x3;
  int cw=0;
  for(int cr=0;cr<4;++cr) {
    if (cr==c)
      continue;
    int rw=0;
    for(int rr=0;rr<4;++rr) {
      if (rr==r)
        continue;
      m3x3.m[cw][rw]=m[cr][rr];
      ++rw;
    }
    ++cw;
  }
  return m3x3.determinant();
}

f32 Matrix4x4::algebraicCofactor(u8 r, u8 c) const {
  f32 cf=cofactor(r,c);
  if (0!=(r+c)%2)
    cf*=-1.f;
  return cf;
}