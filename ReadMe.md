# twoComponentLiquidFoam

An OpenFOAM solver for simulating two-component liquid flows with constant densities.

---

## **Description**
`twoComponentLiquidFoam` is a custom OpenFOAM solver designed to model the flow of **two immiscible liquids** with **constant densities**. The solver is based on the **Volume of Fluid (VoF)** method and is suitable for simulating multiphase flows, such as liquid-liquid interactions, sloshing, or mixing processes.

---

## **Features**
- Simulates **two-component liquid flows** with constant densities.
- Uses the **VoF method** to track the interface between the two liquids.
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

## **Governing Equations**

### **1. Mass Conservation (Continuity Equation)**
For each phase \( k \) (where \( k = 1, 2 \)):
\[
\frac{\partial \alpha_k \rho_k}{\partial t} + \nabla \cdot (\alpha_k \rho_k \mathbf{U}) = 0
\]
where:
- \( \alpha_k \) is the volume fraction of phase \( k \),
- \( \rho_k \) is the density of phase \( k \),
- \( \mathbf{U} \) is the velocity field.

The volume fractions satisfy:
\[
\alpha_1 + \alpha_2 = 1
\]

---

### **2. Momentum Conservation (Navier-Stokes Equation)**
The single momentum equation for the mixture is:
\[
\frac{\partial (\rho \mathbf{U})}{\partial t} + \nabla \cdot (\rho \mathbf{U} \otimes \mathbf{U}) = -\nabla p + \nabla \cdot \left[ \mu (\nabla \mathbf{U} + (\nabla \mathbf{U})^T) \right] + \rho \mathbf{g} + \mathbf{F}_\sigma
\]
where:
- \( \rho = \alpha_1 \rho_1 + \alpha_2 \rho_2 \) is the mixture density,
- \( \mu = \alpha_1 \mu_1 + \alpha_2 \mu_2 \) is the mixture dynamic viscosity,
- \( p \) is the pressure,
- \( \mathbf{g} \) is the gravitational acceleration,
- \( \mathbf{F}_\sigma \) is the surface tension force (if applicable).

---

### **3. Volume Fraction Advection**
The advection equation for the volume fraction \( \alpha_1 \) is:
\[
\frac{\partial \alpha_1}{\partial t} + \nabla \cdot (\alpha_1 \mathbf{U}) + \nabla \cdot (\alpha_1 (1 - \alpha_1) \mathbf{U}_r) = 0
\]
where \( \mathbf{U}_r \) is the relative velocity (compressive term to sharpen the interface).

---

### **4. Additional Models**
- **Turbulence**: Optional turbulence models (e.g., \( k-\varepsilon \), \( k-\omega \)) can be included for turbulent flows.
- **Surface Tension**: The **Continuum Surface Force (CSF)** model can be enabled to account for surface tension effects:
  \[
  \mathbf{F}_\sigma = \sigma \kappa \nabla \alpha_1
  \]
  where \( \sigma \) is the surface tension coefficient and \( \kappa \) is the interface curvature.

---