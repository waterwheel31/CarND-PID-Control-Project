#include "PID.h"
#include <iostream>
#include <cmath>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_, bool p_tra, bool i_tra, bool d_tra) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */

  p_train = p_tra; 
  i_train = i_tra; 
  d_train = d_tra; 
  
  p.push_back(Kp_);
  p.push_back(Ki_);
  p.push_back(Kd_);
  
  std::cout << "p[0]:" << p[0] <<std::endl;
  
  dp.push_back(0.1);
  dp.push_back(0.0001);
  dp.push_back(1.0);
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  i_error += cte; 
  d_error = cte - p_error;
  p_error = cte;

  if(cnt >= 3){ cnt = 0;}
  
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  
  
  return - p[0] * p_error - p[1] * i_error - p[2] * d_error;  // TODO: Add your total error calc here!
}

void PID::UpdateCoefficients(double cte){
	
  std::cout << "Update Coeffcients: "  << cte  << "  cnt:" << cnt << " cnt2: " << cnt2 <<  " p:" << p[0] << "/" << p[1] << "/" << p[2] <<  " dp:" << dp[0] << "/" << dp[1] << "/" << dp[2] <<std::endl;   
  // Twiddle
  
  
  
  // for P 
  double cte_abs = std::abs(cte);
  if (p_train){
      if (cnt2 == 0){

        p[0] += dp[0]; 
        if (cte_abs < min_cte){ 
          min_cte = cte_abs; 
          dp[0] *= 1.01;
        } else {
          p[0] -= 2 * dp[0];
        }
        cnt2 = 1;

      } else {
        if (cte_abs < min_cte){ 
          min_cte = cte_abs; 
          dp[0] *= 1.01;
        } else {
          p[0] += dp[0];
          dp[0] *= 0.99;
        }
        cnt2 = 0;
      }
  }
  
  
  // for D
  double d_error_abs = std::abs(d_error);
  if (d_train){
      if (cnt2 == 0){

        p[2] += dp[2]; 
        if (d_error_abs < min_cte_diff){ 
          min_cte_diff = d_error_abs; 
          dp[2] *= 1.01;
        } else {
          p[2] -= 2 * dp[2];
        }
        cnt2 = 1;

      } else {
        if (d_error_abs < min_cte_diff){ 
          min_cte_diff = d_error_abs; 
          dp[2] *= 1.01;
        } else {
          p[2] += dp[2];
          dp[2] *= 0.99;
        }
        cnt2 = 0;
      }
  }
  
  
  // for I 
  
    double i_error_abs = std::abs(i_error);
  if (i_train){
      if (cnt2 == 0){

        p[1] += dp[1]; 
        if (i_error_abs < min_cte_i){ 
          min_cte_i = i_error_abs; 
          dp[1] *= 1.01;
        } else {
          p[1] -= 2 * dp[1];
        }
        cnt2 = 1;

      } else {
        if (i_error_abs < min_cte_i){ 
          min_cte_i = i_error_abs; 
          dp[1] *= 1.01;
        } else {
          p[1] += dp[1];
          dp[1] *= 0.99;
        }
        cnt2 = 0;
      }
  }
  
  
  /*
  if (cnt2 == 0){
    
    p[cnt] += dp[cnt]; 
    if (cte_abs < min_cte){ 
      min_cte = cte_abs; 
      dp[cnt] *= 1.001;
    } else {
      p[cnt] -= 2 * dp[cnt];
    }
    cnt2 = 1;
  
  } else {
  	if (cte_abs < min_cte){ 
      min_cte = cte_abs; 
      dp[cnt] *= 1.001;
    } else {
      p[cnt] += dp[cnt];
      dp[cnt] *= 0.999;
    }
    cnt += 1; 
    if (cnt==3) {cnt = 0;}
    cnt2 = 0;
  }
  */
  //std::cout << "Update Coeffcients end: " << std::endl;  
}
