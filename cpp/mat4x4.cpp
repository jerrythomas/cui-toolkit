typedef unsigned char byte;
typedef unsigned int  word;

class Mat3x3
 {
  protected :

   float Mat[3][3];

  public :

   Mat3x3();
   void   Mat3x3::Zero();
   void   Mat3x3::Identity();

   Mat3x3 operator *(float f);
   Mat3x3 operator /(float f);

   Mat3x3 operator *(Mat3x3 M);
   Mat3x3 operator +(Mat3x3 M);
   Mat3x3 operator -(Mat3x3 M);

   Mat3x3 operator *=(float f);
   Mat3x3 operator /=(float f);

   Mat3x3 operator *=(Mat3x3 M);
   Mat3x3 operator +=(Mat3x3 M);
   Mat3x3 operator -=(Mat3x3 M);

 };


// Member functions of class Mat3x3


Mat3x3::Mat3x3()
 {
  Zero();
 }

void Mat3x3::Zero()
 {
   Mat[0][0] = Mat[0][1] = Mat[0][2] = Mat[0][3] = 0;
   Mat[1][0] = Mat[1][1] = Mat[1][2] = Mat[1][3] = 0;
   Mat[2][0] = Mat[2][1] = Mat[2][2] = Mat[2][3] = 0;
   Mat[3][0] = Mat[3][1] = Mat[3][2] = Mat[3][3] = 0;
 }

void Mat3x3::Identity()
 {
   Mat[0][1] = Mat[0][2] = Mat[0][3] = 0.0;
   Mat[1][0] = Mat[1][2] = Mat[1][3] = 0.0;
   Mat[2][0] = Mat[2][1] = Mat[2][3] = 0.0;
   Mat[3][0] = Mat[3][1] = Mat[3][2] = 0.0;
   Mat[0][0] = Mat[1][1] = Mat[2][2] = Mat[3][3] = 1.0;
 }


// Operators of class Mat3x3


Mat3x3 Mat3x3::operator *(float f)
 {
  Mat3x3 rvMat;
  byte   i,j;
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      rvMat.Mat[i][j] = Mat[i][j]*f;
  return rvMat;
 }
Mat3x3 Mat3x3::operator /(float f)
 {
  Mat3x3 rvMat;
  byte   i,j;
  if (f)
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      rvMat.Mat[i][j] = Mat[i][j]/f;
  else
   rvMat = MAXFLOAT;
  return rvMat;
 }
Mat3x3 Mat3x3::operator *(Mat3x3 M)
 {
  Mat3x3 Result;
  Result.Zero();
  byte i,j,k;
  for (i=0;i<3;i++)
   for (j=0;j<3;j++)
    for (k=0;k<3;k++)
     Result.Mat[i][k] += Mat[i][j]*M.Mat[j][k];
  return Result;
 }
Mat3x3 Mat3x3::operator +(Mat3x3 M)
 {
  Mat3x3 Result;
  Result.Zero();
  byte i,j;
  for (i=0;i<3;i++)
   for (j=0;j<3;j++)
     Result.Mat[i][j] = Mat[i][j]+M.Mat[i][j];
  return Result;
 }
Mat3x3 Mat3x3::operator -(Mat3x3 M)
 {
  Mat3x3 Result;
  Result.Zero();
  byte i,j;
  for (i=0;i<3;i++)
   for (j=0;j<3;j++)
     Result.Mat[i][j] = Mat[i][j]-M.Mat[i][j];
  return Result;
 }


Mat3x3 Mat3x3::operator *=(float f)
 {
  byte i,j;
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      Mat[i][j] *= f;
  return *this;
 }
Mat3x3 Mat3x3::operator /=(float f)
 {
  byte i,j;
  if (f)
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      Mat[i][j] /= f;
  else
   *this = MAXFLOAT;
  return *this;
 }


Mat3x3 Mat3x3::operator *=(Mat3x3 M)
 {
  Mat3x3 Result;
  Result.Zero();
  byte i,j,k;
  for (i=0;i<3;i++)
   for (j=0;j<3;j++)
    for (k=0;k<3;k++)
     Result.Mat[i][k] += Mat[i][j]*M.Mat[j][k];
  *this = Result;
  return Result;
 }
Mat3x3 Mat3x3::operator +=(Mat3x3 M)
 {
  byte i,j;
  for (i=0;i<3;i++)
   for (j=0;j<3;j++)
    Mat[i][j] += M.Mat[i][j];
  return *this;
 }
Mat3x3 Mat3x3::operator -=(Mat3x3 M)
 {
  byte i,j;
  for (i=0;i<3;i++)
   for (j=0;j<3;j++)
     Mat[i][j] -= M.Mat[i][j];
  return *this;
 }

