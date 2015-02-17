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

#include "stdlib.h"
#include "string.h"
#include "pizza_settings.h"
#include "domain.h"
#include "update.h"
#include "integrate.h"
#include "modify.h"
#include "output.h"
#include "finish.h"
#include "input.h"
#include "timer.h"
#include "error.h"
#include "force.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

PizzaBasicSettings::PizzaBasicSettings(LAMMPS *lmp) : Pointers(lmp) {}

/* ---------------------------------------------------------------------- */

void PizzaBasicSettings::command(int narg, char **arg)
{
    if(narg != 1)
        error->all(FLERR,"pizza_basic_settings does take exactly one arg");
    if(strcmp(arg[0],"default"))
        error->all(FLERR,"pizza_basic_settings currently only supports mode 'default'");

    input->one("atom_style	granular");
    input->one("atom_modify	map array");
    input->one("boundary	m m m");
    input->one("newton		off");
    input->one("units		si");
    input->one("communicate	single vel yes");
    input->one("neighbor	0.002 bin");
    input->one("neigh_modify	delay 0");
    input->one("timestep	0.000025");
}

/* ---------------------------------------------------------------------- */

PizzaPhysicsSettings::PizzaPhysicsSettings(LAMMPS *lmp) : Pointers(lmp) {}

/* ---------------------------------------------------------------------- */

void PizzaPhysicsSettings::command(int narg, char **arg)
{
    if(narg != 1)
        error->all(FLERR,"pizza_physics_settings does take exactly one arg");
    if(strcmp(arg[0],"default"))
        error->all(FLERR,"pizza_physics_settings currently only supports mode 'default'");

    input->one("fix 		m1 all property/global youngsModulus peratomtype 5.e6");
    input->one("fix 		m2 all property/global poissonsRatio peratomtype 0.45");
    input->one("fix 		m3 all property/global coefficientRestitution peratomtypepair 1 0.7");
    input->one("fix 		m4 all property/global coefficientFriction peratomtypepair 1 0.05");
    input->one("pair_style gran model hertz tangential history #Hertzian without cohesion");
    input->one("pair_coeff	* *");
}
/* ---------------------------------------------------------------------- */

PizzaOutputSettings::PizzaOutputSettings(LAMMPS *lmp) : Pointers(lmp) {}

/* ---------------------------------------------------------------------- */

void PizzaOutputSettings::command(int narg, char **arg)
{
    if(narg != 1)
        error->all(FLERR,"pizza_output_settings does take exactly one arg");
    if(strcmp(arg[0],"default"))
        error->all(FLERR,"pizza_output_settings currently only supports mode 'default'");

    input->one("compute		rke all erotate/sphere");
    input->one("thermo_style	custom step atoms ke c_rke f_heattransfer vol");
    input->one("thermo		1000");
    input->one("thermo_modify	lost ignore norm no");
    input->one("compute_modify	thermo_temp dynamic yes");
    input->one("dump		dmp all custom 1000 post/dump*.heatGran id type x y z vx vy vz fx fy fz omegax omegay omegaz radius f_Temp[0] f_heatFlux[0]");
    input->one("variable        step equal step");
    input->one("variable        tsim equal time");
    input->one("fix             extra all print 1000 \"Current time for step ${step}: ${tsim} seconds\" file post/time.txt screen no");
}

