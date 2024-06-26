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

#include "IsrJet.h"
#include "JetScapeLogger.h"
#include "JetScapeSignalManager.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace Jetscape {

IsrJet::IsrJet() : JetEnergyLoss() {
  SetId("IsrJet");
  VERBOSE(8);
}

IsrJet::~IsrJet() {
  // Check if this is all really needed with shared_ptr ...
  JSDEBUG;
}

void IsrJet::InitTask()
{
  JSINFO << "Intialize ISR Jet ..."; //via JetEnergyLossManager::Init() ...";
  JSDEBUG << " --> everything set not via XML for now ...";

  if (GetNumberOfTasks() < 1) {
    JSWARN << " : No valid Energy Loss modules found ...";
    exit(-1);
  }

  // Should be done here too; set to nullptr in JetEnergyLoss header ...
  //inP = nullptr;
  //pShower = nullptr;

  JSINFO << "Found " << GetNumberOfTasks()
         << " ISR Tasks/Modules Initialize them ... ";

   if (GetActive())
     JSINFO << "ISR shower with deltaT = " << GetDeltaT() << " startT = "<<GetStartT() << " and maxT = " << GetMaxT();
   else
     JSINFO << "ISR shower via Main Clock ...";

  // JetScapeTask::InitTasks();
  // Automatically done by framework (s. JetscapeTask::Init)
}

} // end namespace Jetscape
