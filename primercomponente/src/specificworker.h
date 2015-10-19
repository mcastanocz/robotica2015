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

/**
       \brief
       @author authorname
*/







#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>

<<<<<<< HEAD
class QTimer;
=======
>>>>>>> 55200e4b027a25937809b85e37f2d1c871bf01dc
class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
<<<<<<< HEAD
	void newAprilTag(const tagsList &tags);

public slots:
	void compute(); 
	void movimientoRobot(RoboCompLaser::TLaserData ldata);
	void buscador();
	void oritentar();
	void parar();

private:
  
  struct TagsList
  {   
    int visitar=0;
    typedef struct {
	  	 int id;
		float tx;
		float ty;
		float tz;
		float rx;
		float ry;
		float rz;
		QTime tiempo;
      
      void print() const {
		qDebug() << id << tx << tz << tiempo;
		qDebug() << "-------------------------------------";
	  }	
		
    }Tagestruct;
    	
     QMutex mutex;
     QMap <int,Tagestruct> map; 
     void add(const RoboCompAprilTags::tag t)
     {
        
        QMutexLocker ml(&mutex);
	Tagestruct tag;
	tag.id = t.id;
	tag.tx=t.tx;
	tag.ty=t.ty;
	tag.rz=t.tz;
	tag.rx=t.rx;
	tag.ry=t.ry;	
	tag.rz=t.rz;
	map.insert(t.id,tag);
	tag.tiempo=QTime::currentTime();
       
    }
    bool exist (int id){
      
       QMutexLocker ml(&mutex);
     //  borrarMarcas(id);
       return map.contains(id);
      
    }
    Tagestruct get (int id)
    {
      
    QMutexLocker ml(&mutex);
   // borrarMarcas( id);
     return map.find(id).value();
      
    }
    void borrarMarcas(int id)
    {
      if(map.contains(id))
      {
	   
	 Tagestruct t= map.find(id).value();
	 if( t.tiempo.elapsed()>1000)
	  {
	    map.remove(id);
	   std::cout << "Eliminado id "<< id<< std::endl;
	  }
	 
	}
	
      }
      void print()
      {
	   QMapIterator<int, Tagestruct> i(map);
	   while (i.hasNext()) 
	   {
	      i.next();
	      i.value().print();
	   }
      }
  };
  
  
  enum class State {INIT,SEARCH,ORIENT,ADVANCE,STOP};
  State estado =State::INIT;
   TagsList tagslist;
   int currentag;//1,2,3,4
   bool enpared;
};
=======


public slots:
	void compute(); 	

private:
	
};

>>>>>>> 55200e4b027a25937809b85e37f2d1c871bf01dc
#endif

