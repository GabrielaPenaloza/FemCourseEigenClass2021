

#include <iostream>
#include <math.h>
#include "IntRule.h"
#include "IntRule1d.h"
#include "IntRuleQuad.h"
#include "IntRuleTetrahedron.h"
#include "IntRuleTriangle.h"
#include "Topology1d.h"
#include "TopologyTriangle.h"
#include "TopologyQuad.h"
#include "TopologyTetrahedron.h"
#include "DataTypes.h"
#include "Analysis.h"
#include "VTKGeoMesh.h"
#include "ReadGmsh.h"

using std::cout;
using std::endl;
using std::cin;

void Integrate1D(); //Essa declaração é necessária para que a função main possa chamá-la.

int main() {
    Integrate1D(); //chama a função Integrate1D e depois retorna 0 para indicar que o programa foi concluído com sucesso.
    return 0;
}

void Integrate1D (){ //Implementação da função Integrate1D

    // test an integration rule
    // lambda expression
    auto func = [](double x){return x*x;}; //Auto: não precisa especificar explicitamente o tipo de retorno da função (double, int, etc)
    //[]  está vazio, o que significa que a função lambda não captura nenhuma variável externa

    IntRule1d oned(2); //objeto IntRule1d chamado oned é criado com uma ordem de integração de 2
    int np = oned.NPoints(); //O número de pontos de integração definidos na regra oned é armazenado na variável np usando o método NPoints() da classe IntRule1d.
    double integral = 0.; //Variável Local,  armazena o valor da integral calculada
    VecDouble co(1); //Variável Local, é um vetor de coordenadas temporárias (neste caso, de tamanho 1)
    double weight; //Variável Local, armazena os pesos dos pontos de integração
    for (int ip = 0; ip < np; ip++) {
        
        oned.Point(ip, co, weight); //O método Point() da classe IntRule1d é usado para obter as coordenadas e o peso do ponto de integração atual. Os valores são armazenados nas variáveis co e weight.
        double val = func(co[0]);
        integral += val*weight;
    }
    std::cout << "espera se 2/3 obtem se " << integral << std::endl;    
}

/*No geral, este programa realiza uma integração numérica unidimensional de uma função lambda simples (x*x) 
usando uma regra de integração de segunda ordem e, em seguida, imprime o resultado da integral no console.*/


//void Integrate2D(); //Essa declaração é necessária para que a função main possa chamá-la.

//int main() {
   // Integrate2D(); //chama a função Integrate1D e depois retorna 0 para indicar que o programa foi concluído com sucesso.
    //return 0;
//}

void Integrate2D(); //Essa declaração é necessária para que a função main possa chamá-la.

int main() {
    Integrate2D(); //chama a função Integrate1D e depois retorna 0 para indicar que o programa foi concluído com sucesso.
    return 0;
}



void Integrate2D (){ //Implementação da função Integrate1D

    // test an integration rule
    // lambda expression
    auto func = [](VecDouble x){return x[0]*x[0]*x[1]*x[1];}; //Auto: não precisa especificar explicitamente o tipo de retorno da função (double, int, etc)
    //[]  está vazio, o que significa que a função lambda não captura nenhuma variável externa

    IntRuleQuad quadrule(2/*Order*/);
    quadrule.Print(std::cout);
    
    int np = quadrule.NPoints(); //O número de pontos de integração definidos na regra oned é armazenado na variável np usando o método NPoints() da classe IntRule1d.
    double integral = 0.; //Variável Local,  armazena o valor da integral calculada
    VecDouble co(2); //Variável Local, é um vetor de coordenadas temporárias (neste caso, de tamanho 1)
    double weight; //Variável Local, armazena os pesos dos pontos de integração
    for (int ip = 0; ip < np; ip++) {
        
        quadrule.Point(ip, co, weight); //O método Point() da classe IntRule1d é usado para obter as coordenadas e o peso do ponto de integração atual. Os valores são armazenados nas variáveis co e weight.
        double val = func(co);
        integral += val*weight;
    }    std::cout << "espera se 4/9 obtem se " << integral << std::endl;    
}

/*No geral, este programa realiza uma integração numérica unidimensional de uma função lambda simples (x*x) 
usando uma regra de integração de segunda ordem e, em seguida, imprime o resultado da integral no console.*/