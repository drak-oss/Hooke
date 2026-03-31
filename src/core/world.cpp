#include "core/world.h"

int World::addHook(glm::vec2& pos , float radius) {
    int id = nodes.size() ;
    glm::vec2 vel = {0.0f , 0.0f} ;
    nodes.emplace_back(id , NodeType::Hook , pos , vel , 0.0f , radius) ;
    return id ;
}

int World::addMass(glm::vec2& pos , glm::vec2& vel , float mass , float radius) {
    int id = nodes.size() ;
    nodes.emplace_back(id , NodeType::Mass , pos , vel , mass , radius) ;
    return id ;
}

int World::addSpring(int nodeA , int nodeB , float restLength , float stiffness , float damping) {
    int id = springs.size() ;
    springs.emplace_back(id , nodeA , nodeB , restLength , stiffness , damping) ;

    nodes[nodeA].connectedSprings.push_back(id) ;
    nodes[nodeB].connectedSprings.push_back(id) ;

    return id ;
}

void World::initWorld() {
    /*
       ---S3---[M1]---|
       |             S1
       |              |
      [M2]---S2-----[M3]

    */

    glm::vec2 hookPos = {300,300} ;
    glm::vec2 mass1Pos = {300 , 400} , mass2Pos = {100 , 300} , mass3Pos = {500 , 300} ;
    glm::vec2 vel = {0.0f , 0.0f} ;
    int hookid = addHook(hookPos , 10.0f) ;
    int mass1id = addMass(mass1Pos , vel , 10.0f , 10.0f) ;
    int mass2id = addMass(mass2Pos , vel , 10.0f , 10.0f) ;
    int mass3id = addMass(mass3Pos , vel , 10.0f , 10.0f) ;

    addSpring(hookid , mass1id , 40.0f , 1000.0f , 0.005f) ;
    addSpring(hookid , mass3id , 40.0f , 200.0f , 0.005f) ;
    addSpring(hookid , mass2id , 40.0f , 200.0f , 0.005f) ;


    /*// ---------- Hook positions ----------
    glm::vec2 hookCenterPos = {400.0f, 300.0f};
    glm::vec2 hookTopPos    = {400.0f, 100.0f};
    glm::vec2 hookBottomPos = {400.0f, 500.0f};
    glm::vec2 hookLeftPos   = {150.0f, 300.0f};
    glm::vec2 hookRightPos  = {650.0f, 300.0f};

    // ---------- Mass positions ----------
    glm::vec2 centerMassPos = {400.0f, 300.0f};

    glm::vec2 topMassPos    = {400.0f, 200.0f};
    glm::vec2 bottomMassPos = {400.0f, 400.0f};
    glm::vec2 leftMassPos   = {300.0f, 300.0f};
    glm::vec2 rightMassPos  = {500.0f, 300.0f};

    glm::vec2 topLeftPos     = {300.0f, 200.0f};
    glm::vec2 topRightPos    = {500.0f, 200.0f};
    glm::vec2 bottomLeftPos  = {300.0f, 400.0f};
    glm::vec2 bottomRightPos = {500.0f, 400.0f};

    // ---------- Shared initial velocity ----------
    glm::vec2 zeroVel = {0.0f, 0.0f};

    // ---------- Hooks ----------
    int hookCenter = addHook(hookCenterPos, 10.0f);
    int hookTop    = addHook(hookTopPos,    10.0f);
    int hookBottom = addHook(hookBottomPos, 10.0f);
    int hookLeft   = addHook(hookLeftPos,   10.0f);
    int hookRight  = addHook(hookRightPos,  10.0f);

    // ---------- Masses ----------
    int mCenter = addMass(centerMassPos, zeroVel, 10.0f, 10.0f);

    int mTop    = addMass(topMassPos,    zeroVel, 8.0f, 8.0f);
    int mBottom = addMass(bottomMassPos, zeroVel, 8.0f, 8.0f);
    int mLeft   = addMass(leftMassPos,   zeroVel, 8.0f, 8.0f);
    int mRight  = addMass(rightMassPos,  zeroVel, 8.0f, 8.0f);

    int mTL = addMass(topLeftPos,     zeroVel, 6.0f, 6.0f);
    int mTR = addMass(topRightPos,    zeroVel, 6.0f, 6.0f);
    int mBL = addMass(bottomLeftPos,  zeroVel, 6.0f, 6.0f);
    int mBR = addMass(bottomRightPos, zeroVel, 6.0f, 6.0f);

    // ---------- Springs: Hooks to outer masses ----------
    addSpring(hookTop,    mTop,    60.0f, 800.0f, 0.005f);
    addSpring(hookBottom, mBottom, 60.0f, 800.0f, 0.005f);
    addSpring(hookLeft,   mLeft,   60.0f, 800.0f, 0.005f);
    addSpring(hookRight,  mRight,  60.0f, 800.0f, 0.005f);

    // ---------- Springs: Center to cardinal masses ----------
    addSpring(mCenter, mTop,    50.0f, 600.0f, 0.0001f);
    addSpring(mCenter, mBottom, 50.0f, 600.0f, 0.0001f);
    addSpring(mCenter, mLeft,   50.0f, 600.0f, 0.0001f);
    addSpring(mCenter, mRight,  50.0f, 600.0f, 0.0001f);

    // ---------- Springs: Diagonal masses ----------
    addSpring(mTop, mTL,  40.0f, 400.0f, 0.005f);
    addSpring(mTop, mTR,  40.0f, 400.0f, 0.005f);
    addSpring(mBottom, mBL, 40.0f, 400.0f, 0.005f);
    addSpring(mBottom, mBR, 40.0f, 400.0f, 0.005f);

    addSpring(mLeft,  mTL, 40.0f, 400.0f, 0.005f);
    addSpring(mLeft,  mBL, 40.0f, 400.0f, 0.005f);
    addSpring(mRight, mTR, 40.0f, 400.0f, 0.005f);
    addSpring(mRight, mBR, 40.0f, 400.0f, 0.005f);

    // ---------- Cross-bracing (stability + chaos) ----------
    addSpring(mTL, mBR, 120.0f, 300.0f, 0.005f);
    addSpring(mTR, mBL, 120.0f, 300.0f, 0.005f);

    // ---------- Soft tether to center hook ----------
    addSpring(hookCenter, mCenter, 20.0f, 200.0f, 0.005f);*/
}