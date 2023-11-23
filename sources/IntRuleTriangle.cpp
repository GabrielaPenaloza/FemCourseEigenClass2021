/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

///\cond
#include <iostream> 
///\endcond
#include "IntRuleTriangle.h"

IntRuleTriangle::IntRuleTriangle(){
    SetOrder(0);
}

IntRuleTriangle::IntRuleTriangle(int order) {
    SetOrder(order);
}

void IntRuleTriangle::SetOrder(int order) {
    fOrder = order;
    switch (order)
    {
    case 0:
    case 1:
        fPoints.resize(1,2); //(1 ponto, (ksi, eta))
        fWeights.resize(1);

        //Ponto 1
        fPoints(0,0) = 1./3.; //Coordenada ksi
        fPoints(0,1) = 1./3.; //Coordenada eta

        fWeights[0] = 1/2; //Peso é 1, mas se divide por dois devido a área do triángulo
        
        break;
    case 2:
        fPoints.resize(3,2);
        fWeights.resize(3);

        //Ponto 1
        fPoints(0,0) = 1./6.;
        fPoints(0,1) = 2./3.;

        //Ponto 2
        fPoints(1,0) = 1./6.;
        fPoints(1,1) = 1./6.;

        //Ponto 3
        fPoints(2,0) = 2./3.;
        fPoints(2,1) = 1./6.;

        fWeights[0] = 1./6.; //Peso é 1/3, mas se divide por dois devido a área do triángulo
        fWeights[1] = 1./6.;
        fWeights[2] = 1./6.;
        fWeights[3] = 1./6.;

        break; 
    case 3:
        fPoints.resize(4,2);
        fWeights.resize(4);

        //Ponto 1
        fPoints(0,0) = 1./3.;
        fPoints(0,1) = 1./3.;

        //Ponto 2
        fPoints(1,0) = 1./5.;
        fPoints(1,1) = 3./5.;

        //Ponto 3
        fPoints(2,0) = 1./5.;
        fPoints(2,1) = 1./5.;

        //Ponto 4
        fPoints(3,0) = 3./5.;
        fPoints(3,1) = 1./5.;

        fWeights[0] = -9/32; //Peso é -0.5625, mas se divide por dois devido a área do triángulo
        fWeights[1] = 25./96.; //Peso é 0.520833333333333, mas se divide por dois devido a área do triángulo
        fWeights[2] = 25./96.;
        fWeights[3] = 25./96.;

        break;

    case 4:
        fPoints.resize(4,2);
        fWeights.resize(4);

        //Ponto 1
        fPoints(0,0) = 0.445948490915965;
        fPoints(0,1) = 0.108103018168070;

        //Ponto 2
        fPoints(1,0) = 0.445948490915965;
        fPoints(1,1) = 0.445948490915965;

        //Ponto 3
        fPoints(2,0) = 0.108103018168070;
        fPoints(2,1) = 0.445948490915965;

        //Ponto 4
        fPoints(3,0) = 0.091576213509771;
        fPoints(3,1) = 0.816847572980459;

        //Ponto 5
        fPoints(4,0) = 0.091576213509771;
        fPoints(4,1) = 0.091576213509771;

        //Ponto 6
        fPoints(5,0) = 0.816847572980459;
        fPoints(5,1) = 0.091576213509771;


        fWeights[0] = 0.223381589678011; 
        fWeights[1] = 0.223381589678011; 
        fWeights[2] = 0.223381589678011;
        fWeights[3] = 0.109951743655322;
        fWeights[4] = 0.109951743655322;
        fWeights[5] = 0.109951743655322;

        break;

default:
        DebugStop();
        break;
    }



}
