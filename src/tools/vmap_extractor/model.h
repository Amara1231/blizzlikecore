/*
 * Copyright (C) 2011-2012 BlizzLikeCore <http://blizzlike.servegame.com/>
 * Please, read the credits file.
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODEL_H
#define MODEL_H

#include "loadlib/loadlib.h"
#include "vec3d.h"
//#include "mpq.h"
#include "modelheaders.h"
#include <vector>

class Model;
class WMOInstance;
class MPQFile;

Vec3D fixCoordSystem(Vec3D v);

class Model
{
public:
    ModelHeader header;
    ModelVertex *origVertices;
    Vec3D *vertices;
    uint16 *indices;
    size_t nIndices;

    bool open();
    bool ConvertToVMAPModel(char * outfilename);

    bool ok;

    Model(std::string &filename);
    ~Model();

private:
    std::string filename;
    char outfilename;
};

class ModelInstance
{
public:
    Model *model;

    uint32 id;
    Vec3D pos, rot;
    unsigned int d1, scale;
    float w,sc;

    ModelInstance() {}
    ModelInstance(MPQFile &f,const char* ModelInstName, uint32 mapID, uint32 tileX, uint32 tileY, FILE *pDirfile);

};

#endif

