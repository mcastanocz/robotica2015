/*
 *    Copyright (C) 2015 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{

}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	
	timer.start(Period);

	return true;
}

void SpecificWorker::compute( )
{
    try
    {
        RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data 
        std::sort( ldata.begin()+20, ldata.end()-20, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return     a.dist < b.dist; }) ;  //sort laser data from small to large distances using a lambda function.
   
   switch(estado)
    {
      case State::INIT:
	currentag=0;
	estado=State::SEARCH;
	break;
	
      case State::SEARCH: 
 	buscador();
	break;
      case State::ORIENT:
	oritentar();
	
	break;
      case State::ADVANCE:
	movimientoRobot (ldata);
	break;
      case State:: STOP:
	parar();
	break;
    }
    
    }
    catch(const Ice::Exception &ex)
    {
        std::cout << ex << std::endl;
    }
}
void SpecificWorker::parar()
{
  if(currentag==4){
    try {differentialrobot_proxy->setSpeedBase(0,0);} catch (const Ice::Exception &e){std::cout << e << std::endl;};
  }else
    estado=State::SEARCH;
}
  
void SpecificWorker::movimientoRobot(RoboCompLaser::TLaserData ldata){ //Movimiento del robot
    const float threshold = 400; //millimeters
    float rot = 0.6;  //rads per second
    int ruido=0;
    ruido=random()%100;
	
    if( (ldata.data()+20)->dist < threshold)
    {
      enpared=true;
      differentialrobot_proxy->setSpeedBase(5, -rot);
      usleep(rand()%(1500000-100000 + 1) + 100000);  //random wait between 1.5s and 0.1sec
      std::cout << (ldata.data()+20)->dist << std::endl; 
      estado=State::STOP;
      // currentag++;
  //  if(ruido < 10)
    //{
       
    //}
//     else
//     {
//         if((ldata.data()+20)->angle<=0)
//         {
//             std::cout << (ldata.data()+20)->dist << std::endl;
//             differentialrobot_proxy->setSpeedBase(5, -rot);
//         }
//         else
//             differentialrobot_proxy->setSpeedBase(5, rot);
// 
//     }
//         //usleep(rand()%(1500000-100000 + 1) + 100000);  //random wait between 1.5s and 0.1sec
     }
    else
    {
      enpared=false;
        differentialrobot_proxy->setSpeedBase(400, 0); 
    }
  
}
void SpecificWorker:: oritentar()
{
   if(tagslist.exist(currentag))// si existe la marca
   {
     float rot = 0.6;
   TagsList::Tagestruct t= tagslist.get(currentag);
   if(t.tx<0.1 && t.tx>-0.1){//rango de la cordenada X
     estado=State::ADVANCE;
    }else //SI LA X MAYOR 0.1 GIRAS 
    {
       if(enpared==true)
     {
      estado=State::ADVANCE;
     }else{
       
	if(t.tx >=0.1){//si es positivo giras a la derecha
	  try {differentialrobot_proxy->setSpeedBase(5,rot);} catch (const Ice::Exception &e){std::cout << e << std::endl;};
	  usleep(rand()%(1500000-100000 + 1) + 100000);
	}else{//si es negativo a la izquierda
	  try {differentialrobot_proxy->setSpeedBase(5,-rot);} catch (const Ice::Exception &e){std::cout << e << std::endl;};
	  usleep(rand()%(1500000-100000 + 1) + 100000);
	}
      estado=State::SEARCH;
      }
    }
     
     
  }else
    estado=State::SEARCH;
  
}
void SpecificWorker:: buscador(){//Buscador de la marca
  float rot = 0.6;  //rads per second
  float coordenadaX=0,coordenadaZ=0,distancia=0;  
  if(tagslist.exist(currentag))
  {
    TagsList::Tagestruct t= tagslist.get(currentag);
    coordenadaX=t.tx*t.tx;
    coordenadaZ=t.tz*t.tz;
    distancia=coordenadaX+coordenadaZ;
    distancia=sqrt(distancia);
    if(distancia<=0.10){
      std::cout << "Estoy en la marca"<<currentag << std::endl;
      currentag++;
      std::cout << "Paso a la siguiente marca"<< std::endl;
      distancia=0;
    }
    try {differentialrobot_proxy->setSpeedBase(0,0);} catch (const Ice::Exception &e){std::cout << e << std::endl;};
    estado=State::ORIENT;
    return;
   }
   else
   {
    try {differentialrobot_proxy->setSpeedBase(5,rot);} catch (const Ice::Exception &e){std::cout << e << std::endl;};
   }
  
}

void SpecificWorker::newAprilTag(const tagsList& tags)
{
      for(auto t: tags)
      {
	 tagslist.add(t);
	 tagslist.print();
      }
}








