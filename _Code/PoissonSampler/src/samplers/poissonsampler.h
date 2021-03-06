#pragma once
#include "scene/scene.h"
#include "scene/geometry/mesh.h"
#include "raytracing/ray.h"
#include "globals.h"
#include <iostream>

#include "eigen/Eigen/Dense"

#include "poissonbvh.h"
#include "openGL/drawable.h"

class Sample;

class PoissonSampler : public Drawable
{
public:
    //assuming only inputting primitives in scene that ALL need to be filled
    PoissonSampler(Mesh& mesh, Scene& scene, bool isThreeDim);
    ~PoissonSampler() { finalSamples.clear(); delete bvh; delete bbox;}

    // all variables below are initialized in the constructor's list
    Mesh m;
    Scene s;
    Bounds3f* bbox;
    bool threeDim;
    glm::vec3 voxelDim; // number of voxels across each dimension for the grid
    float maxVoxelSize; //actual size of the voxels [cubes so all 3 same val]
    PoissonBVH* bvh;

    Sampler samp;
    int numPoints;
    float RADIUS = 0.3f;

    std::vector<Sample*> finalSamples;

    void initializeVarsAndBVH();
    void poissonAlg();

    glm::vec3 posToGridLoc(glm::vec3 p);
    bool validLocWithinObj(glm::vec3 p);
    bool validWithinOuterBox(glm::vec3 p);

    glm::vec3 randomLocAround(glm::vec3 pos);

    virtual GLenum drawMode() const;
    virtual void create();
};

class Sample {
    public:
        Sample(glm::vec3 gLoc, glm::vec3 wPos, int gId)
            : gridLoc(gLoc), pos(wPos), id(gId) {}
        Sample(Sample* s)
            : gridLoc(s->gridLoc), pos(s->pos), id(s->id) {}
        ~Sample();

        glm::vec3 pos;
        glm::vec3 gridLoc;
        int id;
};
