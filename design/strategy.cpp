#include <iostream>
#include <stdexcept>
#include <iomanip>

class IndexingScheme {
public:
  virtual size_t idx( size_t r, size_t c ) = 0;
  virtual ~IndexingScheme() {}
};

class RowMajor : public IndexingScheme {
  size_t _nCols;
  RowMajor() = delete;
public:
  RowMajor( size_t, size_t numCols ) : _nCols{numCols} {}
  size_t idx( size_t r, size_t c ) { return c + r * _nCols; }
};

class ColMajor : public IndexingScheme {
  size_t _nRows;
  ColMajor() = delete;
public:
  ColMajor( size_t numRows, size_t ) : _nRows{numRows} {}
  size_t idx( size_t r, size_t c ) { return r + c * _nRows; }
};

class Matrix {
  size_t _nRows, _nCols;
  double *_data;
  IndexingScheme *_scheme;
  Matrix() = delete;
  Matrix( const Matrix& matrix ) = delete;
  Matrix& operator=( const Matrix& matrix ) = delete;
public:
  enum Scheme { ROW_MAJOR, COL_MAJOR };

  Matrix( size_t R, size_t C, Scheme type ) : 
    _nRows{R}, 
    _nCols{C}, 
    _data{ new double[R*C] },
    _scheme{ nullptr } {
      if( type == ROW_MAJOR ) {
        _scheme = new RowMajor{ R, C };
      } else if( type == COL_MAJOR ) {
        _scheme = new ColMajor{ R, C };
      } else {
        throw std::runtime_error( "Unknown indexing scheme" );
      }
    }

  ~Matrix() {
    delete [] _data;
    delete _scheme;
  }

  double& data( size_t r, size_t c ) {
    return _data[_scheme->idx( r, c )];
  }

  double data( size_t r, size_t c ) const {
    return _data[_scheme->idx( r, c )];
  }

  double& data( size_t i ) { return _data[i]; }
  double data( size_t i ) const { return _data[i]; }

};

int main() {
  size_t R = 5, C = 5;
  Matrix matrix{ R, C, Matrix::ROW_MAJOR };
  int idx = 0;
  for( size_t r = 0; r < R; ++r ) {
    for( size_t c = 0; c < C; ++c ) {
      matrix.data( r, c ) = ++idx;
    }
  }
  std::cout << "As 2d:\n";
  for( size_t r = 0; r < R; ++r ) {
    for( size_t c = 0; c < C; ++c ) {
      std::cout << std::setw( 2 ) << matrix.data( r, c ) << " ";
    }
    std::cout << '\n';
  }
  std::cout << "\nAs a flat array:\n";
  for( size_t i = 0; i < R * C; ++i ) {
      std::cout << matrix.data( i ) << " ";
  }
  std::cout << '\n';
}
