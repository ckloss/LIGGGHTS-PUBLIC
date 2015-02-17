/* ----------------------------------------------------------------------
   LIGGGHTS® - LAMMPS Improved for General Granular and Granular Heat
   Transfer Simulations

   LIGGGHTS® is part of CFDEM®project
   www.liggghts.com | www.cfdem.com

   Christoph Kloss, christoph.kloss@cfdem.com
   Copyright 2012-     DCS Computing GmbH, Linz

   LIGGGHTS® and CFDEM® are registered trade marks of DCS Computing GmbH,
   the producer of the LIGGGHTS® software and the CFDEM®coupling software
   See http://www.cfdem.com/terms-trademark-policy for details.

   LIGGGHTS® is based on LAMMPS
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level directory.
------------------------------------------------------------------------- */

#ifdef COMMAND_CLASS

CommandStyle(pizza_basic_settings,PizzaBasicSettings)
CommandStyle(pizza_physics_settings,PizzaPhysicsSettings)
CommandStyle(pizza_output_settings,PizzaOutputSettings)

#else

#ifndef LMP_PIZZA_SETTINGS_H
#define LMP_PIZZA_SETTINGS_H

#include "pointers.h"

namespace LAMMPS_NS {

class PizzaBasicSettings : protected Pointers {
 public:
  PizzaBasicSettings(class LAMMPS *);
  void command(int, char **);
};
class PizzaPhysicsSettings : protected Pointers {
 public:
  PizzaPhysicsSettings(class LAMMPS *);
  void command(int, char **);
};
class PizzaOutputSettings : protected Pointers {
 public:
  PizzaOutputSettings(class LAMMPS *);
  void command(int, char **);
};

}

#endif
#endif
