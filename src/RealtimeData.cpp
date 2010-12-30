
/*
 * Copyright (c) 2009 Justin F. Knotzke (jknotzke@shampoo.ca)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "RealtimeData.h"

RealtimeData::RealtimeData()
{
    name[0] = '\0';
    watts = hr = speed = cadence  = load = 0;
    time = 0;
}

void RealtimeData::setName(char *name)
{
    strcpy(this->name, name);
}
void RealtimeData::setWatts(double watts)
{
    this->watts = watts;
}
void RealtimeData::setHr(double hr)
{
    this->hr = hr;
}
void RealtimeData::setTime(long time)
{
    this->time = time;
}
void RealtimeData::setSpeed(double speed)
{
    this->speed = speed;
}
void RealtimeData::setCadence(double aCadence)
{
    cadence = aCadence;
}
void RealtimeData::setLoad(double load)
{
    this->load = load;
}
char *
RealtimeData::getName()
{
    return name;
}
double RealtimeData::getWatts()
{
    return watts;
}
double RealtimeData::getHr()
{
    return hr;
}
long RealtimeData::getTime()
{
    return time;
}

double RealtimeData::getSpeed()
{
    return speed;
}
double RealtimeData::getCadence()
{
    return cadence;
}
double RealtimeData::getLoad()
{
    return load;
}
