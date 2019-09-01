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

#ifndef LIQUEFIERBASE_H
#define LIQUEFIERBASE_H


//#include "JetScapeModuleBase.h"
//#include "FluidDynamics.h"
//#include "FluidCellInfo.h"
#include "JetClass.h"
//#include "JetScapeWriter.h"
//#include "PartonShower.h"
//#include "PartonPrinter.h"
//#include "MakeUniqueHelper.h"
//#include <random>

#include <array>
#include <vector>
#include "RealType.h"

namespace Jetscape {

class Droplet {
 private:
    std::array<Jetscape::real, 4> xmu;
    std::array<Jetscape::real, 4> pmu;

 public:
    Droplet() = default;
    Droplet(std::array<Jetscape::real, 4> x_in,
            std::array<Jetscape::real, 4> p_in) {
        xmu = x_in; pmu = p_in;
    }
    ~Droplet() {};

    std::array<Jetscape::real, 4> get_xmu() const {
        return(xmu);
    }

    std::array<Jetscape::real, 4> get_pmu() const {
        return(pmu);
    }
};

class LiquefierBase {
 private:
    std::vector<Droplet> dropletlist;

 public:
    LiquefierBase() = default;
    ~LiquefierBase() {Clear();}

    void add_a_droplet(Droplet droplet_in) {
        dropletlist.push_back(droplet_in);
    }

    Droplet get_a_droplet(const int idx) const {return(dropletlist[idx]);}

    void add_hydro_sources(std::vector<Parton> &pIn,
                           std::vector<Parton> &pOut);
 

    int get_dropletlist_size() const {return(dropletlist.size());}

    Jetscape::real get_dropletlist_total_energy() const;

    virtual void smearing_kernel(Jetscape::real tau, Jetscape::real x,
                                 Jetscape::real y, Jetscape::real eta,
                                 const Droplet drop_i,
                                 std::array<Jetscape::real, 4> &jmu) const {
        jmu = {0, 0, 0, 0};
    }

    void get_source(Jetscape::real tau, Jetscape::real x,
                    Jetscape::real y, Jetscape::real eta,
                    std::array<Jetscape::real, 4> &jmu) const;

    virtual void Clear();
};

};

#endif  // LIQUEFIERBASE_H
