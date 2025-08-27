# twoComponentLiquidFoam

An OpenFOAM solver for simulating two-component liquid flows with constant densities.

---

## **Description**
`twoComponentLiquidFoam` is a custom OpenFOAM solver designed to model the flow of **two mixed liquids** with **constant densities**. The solver is based on the **Volume of Fluid (VoF)** method and is suitable for simulating mixing processes.

---

## **Features**
- Simulates **two-component liquid flows** with constant densities.
- Supports **transient simulations** with adjustable time stepping.
- Compatible with OpenFOAM's standard boundary conditions and turbulence models.

---

## **Requirements**
- OpenFOAM (2412 or later recommended)
- C++ compiler (GCC, Clang)
- Basic knowledge of OpenFOAM case setup

---

## **Installation**

```bash
git clone https://github.com/PavlovEgor/twoComponentLiquidFoam.git
cd twoComponentLiquidFoam
wmake
```

