#ifndef PID_H
#define PID_H
#include <limits>
#include <vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_, bool p_tra, bool i_tra, bool d_tra);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();
  
  void UpdateCoefficients(double cte);

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;
  
  /**
   * PID Coefficients
   */ 
  std::vector <double> p; 
  std::vector <double> dp; 
  
  int cnt = 0;
  int cnt2 = 0;
  double torrelance = 0.0001; 
  
  bool p_train;
  bool i_train; 
  bool d_train; 
  
  float min_cte = std::numeric_limits<float>::infinity();
  float min_cte_diff = std::numeric_limits<float>::infinity();
  float min_cte_i = std::numeric_limits<float>::infinity();
};

#endif  // PID_H