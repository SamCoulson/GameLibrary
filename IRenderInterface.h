#ifndef INC_IRENDERINTERFACE_H
#define INC_IRENDERINTERFACE_H

#include <string>
#include <list>
#include "Globals.h"
/*
typedef struct imageList_
{
	int x, y;
	UINT imageID;


}imageData_s;
*/

using namespace std;

class IRenderInterface
{
public:
	IRenderInterface(){};
	~IRenderInterface(){}; // Must use virtual deconstructors becasue when the interface is destroyed THIS gets called not the
	// Deconstrucotrs of the derived classes themselves.

	//virtual bool Initialise(){};
//	virtual unsigned int RegisterImage( std::string ) = 0;
//	virtual bool RenderByID(int pos_x, int pos_y, unsigned int ImageID, const Rect*) = 0;
	virtual bool UpdateScreen() = 0;
	virtual bool RenderText(string, int pos_x, int pos_y, unsigned int r, unsigned int g, unsigned int b ) = 0;
	virtual bool FillRect(const Rect &rect, UINT r, UINT g, UINT b) = 0;
	virtual void ClearScreen(UINT r, UINT g, UINT b) = 0;

	virtual UINT GetImageWidth( UINT imageID ) const = 0;
	virtual UINT GetImageHeight( UINT imageID ) const = 0;

	// virtual int DrawLine(int start_x, int start_y, int end_x, int end_y, UINT r, UINT g, UINT b ) = 0;

	void SetX( UINT ID, int& );
	void SetY( UINT ID, int& );

protected:

	//list< imageData_s* > imageList;

private:

};




#endif // INC_IRENDERINTERFACE_H
