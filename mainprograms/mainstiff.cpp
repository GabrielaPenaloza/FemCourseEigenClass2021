#include <iostream>
#include <math.h>
#include "VTKGeoMesh.h"
#include "Geom1d.h"
#include "CompElementTemplate.h"
#include "Shape1d.h"
#include "CompMesh.h"
#include "GeoElementTemplate.h"
#include "GeoMesh.h"
#include "Poisson.h"


using namespace std;


void CallStiffFunc(); //Declaração da função

int main() {
    CallStiffFunc(); //Chamada da função
    return 0; //Deve retornar um valor enteiro
}

void CallStiffFunc(){
    
    // Criar nos com coordenadas e adicionando na malha geom[etrica]
    const int dim = 1; //Unidimensional
    const int numnodes = 2; //dois nós em um elemento
    GeoMesh gmesh; //gmesh objeto de GeoMesh. Malha geométrica
    gmesh.SetDimension(dim);
    gmesh.SetNumNodes(numnodes);
    GeoNode gnod0, gnod1; //gnod0 e gnod1 são objetos de GeoNode //criando nodos
    VecDouble co0(1), co1(1); //objetos co0 e co1, são usados para armazenar as coordenadas dos nós gnod0 e gnod1. Cada um deles é inicializado com uma dimensão de 1.
    co0 << 0.;
    co1 << 4.;
    gnod0.SetCo(co0); //Atribuem as coordenadas definidas anteriormente aos nós gnod0 e gnod1
    gnod1.SetCo(co1);
    gmesh.Node(0) = gnod0; //0 e 1, são as posiçãoes as quais são atribuidos os nós gnod0 e gnod1
    gmesh.Node(1) = gnod1; 
    

    //Criando elemento geom[etrico e se auto adicionando na malha geomtrica]
    int materialid = 0;
    VecInt nodeindices(2); //vetor com indices dos nós na malha
    nodeindices << 0,1;
    int index = 0;
//    const VecInt &nodeindices, int materialid, GeoMesh *gmesh, int index
    GeoElementTemplate<Geom1d> geo(nodeindices,materialid,&gmesh,index); //Criação de um Elemento Geométrico
    

    // Criando malha computacional e setando a ordem polinomial padrao
    CompMesh cmesh(&gmesh);
    cmesh.SetDefaultOrder(1); //Representa a malha computacional associada à malha geométrica. Poinômios de grau 1.
    

    // Criando MathStatement de equacao de Poisson e adicionando na malha computacional
    MatrixDouble perm(3,3);
    perm.setIdentity(); //Preenche a matriz com os valores de uma matriz identidade. DIagonal = 1.
//    perm(1,1) = 2.;
    Poisson poi(materialid, perm); //Poisson é um filho de mathStatement, class Poisson : public MathStatement
    cmesh.SetMathStatement(materialid, &poi); //
    

//Cuando crio el elemento computacional en base al elemenro geoétruco  con material del elementos geométrico,  ese es alugado en MathStatemenr
//Criando elelemto omputacional baseado em elemento geometrico, se adicionado na malha computacional e calculando a matriz de rigidez e vetor de carga
   CompElementTemplate<Shape1d> cel(index,&cmesh,&geo); // se autoadiciona en la malla con este comando
    MatrixDouble ek(2,2),ef(2,1);
    cel.CalcStiff(ek, ef);
    cout << ek << endl;
    cout << ef << endl;


}
