#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <vector>
#include <string>

class VisualCodebook
{
 public:
  VisualCodebook(int k=0);
  void constructCodebook(std::string img_path, int img_count);
  void saveCodebook(std::string path);
  void loadCodebook(std::string path);
  std::vector<int> getCodewords(IplImage& img);
  const int numCenters() const { return static_cast<const int>(k_); }
 protected:
  int k_;
  std::vector<std::vector<float> > centers_;
  CvMat* cv_centers_;
};
