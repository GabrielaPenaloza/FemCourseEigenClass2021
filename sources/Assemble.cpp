/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Assemble.h"
#include "CompMesh.h"
#include "GeoMesh.h"
#include "MathStatement.h"
#include "CompElement.h"



Assemble::Assemble() {
}

Assemble::Assemble(CompMesh *mesh) {
    cmesh = mesh;
}

Assemble::Assemble(const Assemble &copy) {
    cmesh = copy.cmesh;
}

Assemble &Assemble::operator=(const Assemble &copy) {
    cmesh = copy.cmesh;
    return *this;
}

void Assemble::SetMesh(CompMesh *mesh) {
    cmesh = mesh;
}

int64_t Assemble::NEquations() {
    int64_t neq = 0;
    int64_t i, ncon = cmesh->GetDOFVec().size();
    for (i = 0; i < ncon; i++) {
        DOF dof = cmesh->GetDOF(i);
        int64_t dofsize = dof.GetNShape() * dof.GetNState();
        neq += dofsize;
    }
    return neq;
}

void Assemble::OptimizeBandwidth() {    
}

void Assemble::Compute(SparseMat &globmat, MatrixDouble &rhs) {
    
    auto neq = NEquations();
    
    globmat.resize(neq, neq);
    globmat.setZero();
    rhs.resize(neq, 1);
    rhs.setZero();
    
    int64_t nelem = cmesh->GetGeoMesh()->NumElements();
    for (int el = 0; el < nelem; el++) {
        CompElement *cel = cmesh->GetElement(el);

        int nshape = cel->NShapeFunctions();
        int nstate = cel->GetStatement()->NState();
        
        MatrixDouble ek(nstate * nshape, nstate * nshape);
        MatrixDouble ef(nstate * nshape, 1);
        ek.setZero();
        ef.setZero();

        cel->CalcStiff(ek, ef);
        const int neqel =nshape*nstate;
        //Criar vetor de indices de destino
        VecInt destind(neqel);
        destind.setZero();
        int64_t ndof = cel -> NDOF(); //pode ser const int64_t. int64_t es para recibir muchisimos dados
        int count = 0;
        for(int i=0;i<ndof;i++){
            DOF& dofi = cel -> GetDOF(i);
           const int64_t firsteq = dofi.GetFirstEquation();
           const int64_t neqdof = dofi.GetNShape()*dofi.GetNState();
           for(int ieqdof=0; ieqdof < neqdof;ieqdof++){
                destind[count++] = firsteq+ieqdof;

           }

        }
    

        //+++++++++++++++++ YA ESTÁ IMPLEMENTADA
        //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
        //DebugStop();
        //+++++++++++++++++
        //Utiliazr destind para asseblar ek e ef em mglob,at e rhs.

        for(int i=0;i<neqel;i++){
            const int64_t dest_i = destind[i];
            rhs(dest_i,0) += ef(i,0); // le coloca la posición que debe ser puesto en la global 
            for(int j=0; j < neqel;j++){
                const int64_t dest_j = destind[j];
                globmat.coeffRef(dest_i,dest_j) += ek(i,j);
            }
        }
    }
}
