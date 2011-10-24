#ifndef ARRAY3D_HH
#define ARRAY3D_HH

#include <vector>
#include <cassert>

template <class T>
class Array3d
{
 public:

   Array3d();
   Array3d(unsigned nx, unsigned ny, unsigned nz);
   
   T& operator()(unsigned index);
   T& operator()(unsigned ix, unsigned iy, unsigned iz);

   T*** cArray();
   const T*** cArray() const;
   
   unsigned const size();
   void resize(unsigned nx, unsigned ny, unsigned nz);
   
   unsigned const tupleToIndex(unsigned ix, unsigned iy, unsigned iz);

 private:
   void pointerSetup();
   
   unsigned nx_;
   unsigned ny_;
   unsigned nz_;
   std::vector<T> data_;
   T*** cArray_;
};

template <class T> inline
Array3d<T>::Array3d()
: nx_(0), ny_(0), nz_(0), data_(0), cArray_(NULL);
{
}

template <class T> inline
Array3d<T>::Array3d(unsigned nx, unsigned ny, unsigned nz)
: nx_(nx), ny_(ny), nz_(nz), data_(nx*nz*nz)
{
   pointerSetup();
}


template <class T> inline
T& Array3d<T>::operator()(unsigned index)
{
   return data_[index];
}

template <class T> inline
T& Array3d<T>::operator()(unsigned ix, unsigned iy, unsigned iz)
{
   return data_[tupleToIndex(ix, iy, iz)];
}

template <class T> inline
T*** Array3d<T>::cArray()
{
   return cArray_;
}

template <class T> inline
const T*** Array3d<T>::cArray() const
{
   return cArray_;
}

template <class T> inline
unsigned const Array3d<T>::size()
{
   return nx_*ny_*nz_;
}



template <class T> inline 
void Array3d<T>::resize(unsigned nx, unsigned ny, unsigned nz)
{
   assert(nx_ == 0 && ny_ == 0 && nz_ == 0);
   data_.resize(nx*ny*nz);
   nx_ = nx;
   ny_ = ny;
   nz_ = nz;
   pointerSetup();
}
			

template <class T> inline 
unsigned const Array3d<T>::tupleToIndex(unsigned ix, unsigned iy, unsigned iz)
{
   return iz + nz_*(iy + ny_*(ix));
//   return ix + nx_*(iy + ny_*(iz));
}

template <class T> inline
void Array3d<T>::pointerSetup()
{
   cArray_ = (T***) malloc(sizeof(T**)*nx_);
   for (unsigned ii=0; ii<nx_; ++ii)
   {
      cArray_[ii] = (T**) malloc(sizeof(T*)*ny_);
      for (unsigned jj=0; jj<ny_; ++jj)
	 cArray_[ii][jj] = &data_[0] + nz_*(jj + ny_*(ii)); 
   }
}


#endif

