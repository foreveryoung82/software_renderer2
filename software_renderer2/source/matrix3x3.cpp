#include "matrix3x3.h"
#include <cmath>
#include <algorithm>

Matrix3x3 Matrix3x3::make(Vec3 const& u, Vec3 const& v, Vec3 const& w) {
  Matrix3x3 matrix;
  matrix.m[0][0]=u[0];
  matrix.m[0][1]=u[1];
  matrix.m[0][2]=u[2];
  matrix.m[1][0]=v[0];
  matrix.m[1][1]=v[1];
  matrix.m[1][2]=v[2];
  matrix.m[2][0]=w[0];
  matrix.m[2][1]=w[1];
  matrix.m[2][2]=w[2];
  return matrix;
}

Matrix3x3 Matrix3x3::makeIdentity() {
  Matrix3x3 matrix;
  matrix.m[0][0]=1;
  matrix.m[0][1]=0;
  matrix.m[0][2]=0;
  matrix.m[1][0]=0;
  matrix.m[1][1]=1;
  matrix.m[1][2]=0;
  matrix.m[2][0]=0;
  matrix.m[2][1]=0;
  matrix.m[2][2]=1;
  return matrix;
}

Matrix3x3 Matrix3x3::makeAffine(Vec2 const& u, Vec2 const& v, Vec2 const& w) {
  Matrix3x3 matrix;
  matrix.m[0][0]=u[0];
  matrix.m[0][1]=u[1];
  matrix.m[0][2]=0;
  matrix.m[1][0]=v[0];
  matrix.m[1][1]=v[1];
  matrix.m[1][2]=0;
  matrix.m[2][0]=w[0];
  matrix.m[2][1]=w[1];
  matrix.m[2][2]=1;
  return matrix;
}

Matrix3x3 Matrix3x3::makeTranslation(Vec2 const& t) {
  Matrix3x3 matrix=makeIdentity();
  matrix.m[2][0]=t.x;
  matrix.m[2][1]=t.y;
  return matrix;
}

Matrix3x3 Matrix3x3::makeScale(Vec2 const& s) {
  Matrix3x3 matrix=makeIdentity();
  matrix.m[0][0]=s.x;
  matrix.m[1][1]=s.y;
  return matrix;  
}

Matrix3x3 Matrix3x3::makeRotation(f32 radian) {
  Matrix3x3 matrix=makeIdentity();
  f32 c=std::cosf(radian);
  f32 s=std::sinf(radian);
  matrix.m[0][0]=c;
  matrix.m[1][0]=-s;
  matrix.m[0][1]=s;
  matrix.m[1][1]=c;
  return matrix;   
}

Matrix3x3 Matrix3x3::makeXShear(f32 factor) {
  Matrix3x3 matrix=makeIdentity();
  matrix.m[1][0]=factor;
  return matrix;     
}

Matrix3x3 Matrix3x3::makeYShear(f32 factor) {
  Matrix3x3 matrix=makeIdentity();
  matrix.m[0][1]=factor;
  return matrix;    
}

const f32* Matrix3x3::begin() const {
  return &m[0][0];
}

f32* Matrix3x3::begin() {
  return const_cast<f32*>(const_cast<const Matrix3x3*>(this)->begin());
}

const f32* Matrix3x3::end() const {
  const int num=3;
  return (begin()+num*num);
}

f32* Matrix3x3::end() {
  return const_cast<f32*>(const_cast<const Matrix3x3*>(this)->end());
}

bool Matrix3x3::operator==(Matrix3x3 const& rhs) const {
  const bool ret=std::equal(begin(),end(),rhs.begin());
  return ret;
}

Matrix3x3 Matrix3x3::operator+(Matrix3x3 const& rhs) const {
  Matrix3x3 ret;
  std::transform(begin(),end(),rhs.begin(),ret.begin(),
    [](u8 a,u8 b)->u8{return a+b;});
  return ret;
}

Matrix3x3& Matrix3x3::operator+=(Matrix3x3 const& rhs) {
  std::transform(begin(),end(),rhs.begin(),begin(),
    [](u8 a,u8 b)->u8{return a+b;});
  return *this;
}

Matrix3x3 Matrix3x3::operator-(Matrix3x3 const& rhs) const {
  Matrix3x3 ret;
  std::transform(begin(),end(),rhs.begin(),ret.begin(),
    [](u8 a,u8 b)->u8{return a-b;});
  return ret;
}

Matrix3x3& Matrix3x3::operator-=(Matrix3x3 const& rhs) {
  std::transform(begin(),end(),rhs.begin(),begin(),
    [](u8 a,u8 b)->u8{return a-b;});
  return *this;
}

Matrix3x3 Matrix3x3::operator-() const {
  Matrix3x3 ret;
  std::transform(begin(),end(),ret.begin(),[](u8 a)->u8{return -a;});
  return ret;
}

Matrix3x3 Matrix3x3::operator*(f32 factor) const {
  Matrix3x3 ret;
  std::transform(begin(),end(),ret.begin(),
    [factor](f32 v)->f32{return v*factor;});
  return ret;
}

Matrix3x3& Matrix3x3::operator*=(f32 factor) {
  std::transform(begin(),end(),begin(),
    [factor](f32 v)->f32{return v*factor;});
  return *this;  
}

Matrix3x3 Matrix3x3::operator*(Matrix3x3 const& rhs) const {
  Matrix3x3 ret;
  const int num=3;
  for (int c=0;c<num;++c) {
    for (int r=0;r<num;++r) {
      ret.m[c][r]=m[0][r]*rhs.m[c][0]+m[1][r]*rhs.m[c][1]+m[2][r]*rhs.m[c][2];
    }
  }
  return ret;
}

Matrix3x3& Matrix3x3::operator*=(Matrix3x3 const& rhs) {
  Matrix3x3 t=*this*rhs;
  *this=t;
  return *this;
}

Vec3 Matrix3x3::operator*(Vec3 const& rhs) const {
  Vec3 ret;
  const int num=3;
  for (int r=0;r<num;++r) {
    ret.m[r]=m[0][r]*rhs.m[0]+m[1][r]*rhs.m[1]+m[2][r]*rhs.m[2];
  }
  return ret;  
}

Vec2 Matrix3x3::transformVector(Vec2 const& v) const {
  Vec3 v3=Vec3::make(v.x,v.y,0);
  Vec3 ret=*this*v3;
  return Vec2::make(ret);
}

Vec2 Matrix3x3::transformPoint(Vec2 const& p) const {
  Vec3 v3=Vec3::make(p.x,p.y,1);
  Vec3 ret=*this*v3;
  return Vec2::make(ret);
}

Matrix3x3 Matrix3x3::inverse() const {
  Matrix3x3 ret;
  const int num=3;
  const f32 inverse_determinant=1.f/determinant();
  for (int i=0;i<3;++i) {
    for (int j=0;j<3;++j) {
      ret.m[i][j]=inverse_determinant*algebraicCofactor(j,i);
    }
  }
  return ret;
}

Matrix3x3 Matrix3x3::transpose() const {
  Matrix3x3 ret;
  const int num=3;
  for (int c=0;c<num;++c) {
    for (int r=0;r<num;++r) {
      ret.m[c][r]=m[r][c];
    }
  }
  return ret;
}

f32 Matrix3x3::determinant() const {
  // Laplace expansion by 1th row
  f32 ret=m[0][0]*cofactor(0,0)+
              -m[0][1]*cofactor(0,1)+
              m[0][2]*cofactor(0,2);
   return ret;
}

f32 Matrix3x3::cofactor(u8 i, u8 j) const {
  const int num=3;
  int i0=(i+1)%3;
  int i1=(i+2)%3;
  if (i0>i1)
    std::swap(i0, i1);
  int j0=(j+1)%3;
  int j1=(j+2)%3;
  if (j0>j1)
    std::swap(j0, j1);
  const f32 ret=(m[i0][j0]*m[i1][j1]-m[i0][j1]*m[i1][j0]);
  return ret;
}

f32 Matrix3x3::algebraicCofactor(u8 i, u8 j) const {
  f32 cf=cofactor(i,j);
  if (0!=(i+j)%2)
    cf*=-1.f;
  return cf;
}