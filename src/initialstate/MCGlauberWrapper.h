/*******************************************************************************
 * Copyright (c) The JETSCAPE Collaboration, 2018
 *
 * Modular, task-based framework for simulating all aspects of heavy-ion collisions
 * 
 * For the list of contributors see AUTHORS.
 *
 * Report issues at https://github.com/JETSCAPE/JETSCAPE/issues
 *
 * or via email to bugs.jetscape@gmail.com
 *
 * Distributed under the GNU General Public License 3.0 (GPLv3 or later).
 * See COPYING for details.
 ******************************************************************************/

#ifndef MCGlauberWrapper_H
#define MCGlauberWrapper_H

#include <memory>

#include "JetScapeModuleBase.h"
#include "InitialState.h"
#include "JetScapeLogger.h"
#include <MakeUniqueHelper.h>
#include "InitialState.h"
#include "Glauber.h"
#include "Parameters.h"
#include "EventGenerator.h"
using namespace Jetscape;

class MCGlauberWrapper : public Jetscape::InitialState {
  // this is wrapper class to read external files that
  // stores initial number of binary collisions and corresponding
  // configurations
public:
  MCGlauberWrapper();
  ~MCGlauberWrapper() {}

  /** Reads the input parameters from the XML file under the tag  <IS>. Calls InitTask(); This explicit call of InitTask() can be used for actual initialization of modules such as @a Trento if attached as a @a polymorphic class. It also initializes the tasks within the current module.
      @sa Read about @a polymorphism in C++.
   */
  //void Init();

  /** Default Exec() function. It can be overridden by other tasks.
   */
  void Exec();

  /** Default Clear() function. It can be overridden by other tasks.
   */
  void Clear();

  void InitTask();

  /** Default Write() function. It can be overridden by other tasks.
      @param w A pointer to the JetScapeWriter class.
   */
  virtual void Write(weak_ptr<JetScapeWriter> w) {}

  /** Generated number of binary collisions.
  */
  double GetNcoll() { return(static_cast<double>(ncoll_)); }

  void SampleABinaryCollisionPoint(double &t, double &x,
                                   double &y, double &z);
  double Get_total_nucleon_density_lab(double t, double x,
                                       double y, double z);
  double Get_target_nucleon_density_lab(double t, double x,
                                        double y, double z);
  double Get_projectile_nucleon_density_lab(double t, double x,
                                            double y, double z);
private:
 // std::vector<CollisionEvent> collision_information_;
  std::unique_ptr<MCGlb::Glauber> MCGlauber_ptr_;
  std::unique_ptr<MCGlb::EventGenerator> mc_gen_;
  std::vector<double> binary_collision_t_;
  std::vector<double> binary_collision_x_;
  std::vector<double> binary_collision_y_;
  std::vector<double> binary_collision_z_;

  MCGlb::Parameters parameter_list_;
  std::shared_ptr<RandomUtil::Random> ran_gen_ptr_;
  std::shared_ptr<std::uniform_int_distribution<int>> rand_int_ptr_;
  int ncoll_ = -1;
  // Allows the registration of the module so that it is available to be
  // used by the Jetscape framework.
  static RegisterJetScapeModule<MCGlauberWrapper> reg;
};

#endif  // MCGlauberWrapper_H
