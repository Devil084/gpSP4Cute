/* gpsp4cute
 *
 * Copyright (C) 2011 Summeli <summeli@summeli.fi>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "rightbuttonwidget.h"
#include "buttonpositions.h"
#include "input.h"

#include <qmath.h>

const int KCenter_x  = 85;
const int KCenter_y  = 275;

const int BUTTONS_CENTER_RIGHT = KCenter_x + 10;
const int BUTTONS_CENTER_LEFT = KCenter_x - 10;
const int BUTTONS_CENTER_TOP  = KCenter_y - 10;
const int BUTTONS_CENTER_BOTTOM = KCenter_y + 10;

const int BUTTONS_TOP = 200 - 30;

const int SELECT_LEFT = BUTTON_WIDTH - SMALLBUTTON_WIDTH / 2;
const int R_TOP = MENU_HEIGHT + SMALLBUTTON_HEIGHT;

rightbuttonwidget::rightbuttonwidget(QObject *parent)
    : QObject(parent), m_buttonSettings(0)
{
}

rightbuttonwidget::~rightbuttonwidget()
{

}


quint32 rightbuttonwidget::getGpspKeys( int x, int y )
{
    quint32 key = 0;
    if(  y <= MENU_HEIGHT )
        {
        //select or start was pressed
        if( x > SELECT_LEFT )
            key = BUTTON_SELECT;
        else
             key = BUTTON_START;
        }
    else if(  y > MENU_HEIGHT && y <= R_TOP )
        {
        //R was pressed
        key = BUTTON_R;
        }

    else if ((y > BUTTONS_CENTER_TOP ) && (y < BUTTONS_CENTER_BOTTOM ) && (x > BUTTONS_CENTER_LEFT )
          && (x < BUTTONS_CENTER_RIGHT ))
        {
       // Inside center circle of dpad, let's return both A and B
        key += BUTTON_B;
        key += BUTTON_A;
         }
    else if ( y > BUTTONS_TOP )
        {
        qreal x_coord = x - KCenter_x;
        qreal y_coord = y - KCenter_y;

        qreal r = qAtan2(y_coord,x_coord);

        r = (r * 180 )/ KPi; //convert radians to degrees

        //lets use full circle instead of negative angles
        if (r < 0)
                {
                r = 360 + r;
                }

        qint32 angle = qRound(r);


        //360 degrees is divided into 2 sectors.
       /* if (angle >= 226|| angle < 55 )
            {
            //A button was pressed
            key += BUTTON_A;
            }
        else
            {
            key += BUTTON_B;
            }*/
        //360 degrees is divided into 2 sectorss
        if (angle >= 248|| angle < 23)
            {
            //A button was pressed
            key += BUTTON_A;
            }
        else if (angle >= 23 && angle < 68 && m_buttonSettings )
            {
            //A and B key was pressed
            key += BUTTON_B;
            key += BUTTON_A;
            }
        else if (angle >= 68 && angle < 203)
            {
            //B key was pressed
            key += BUTTON_B;
            }
        else if (angle >= 203 && angle < 248 && m_buttonSettings )
            {
            //A and B key was pressed
            key += BUTTON_B;
            key += BUTTON_A;
            }
        }
        return key;
}

 void rightbuttonwidget::setButtonSettings( int buttonSettings )
 {
     m_buttonSettings = buttonSettings;
 }
