#include "pch.h"
#include "CMath.h"


float CMath::calcDistance(CVertex* vertex1, CVertex* vertex2) {
    return sqrt(pow((vertex2->GetX()-vertex1->GetX()),2)+ pow((vertex2->GetY() - vertex1->GetY()), 2));
}

float CMath::calcCrossProduct(CVector* a, CVector* b) {
    return a->GetX() * b->GetY() - a->GetY() * b->GetX();
}

float CMath::calcInnerProduct(CVector* a, CVector* b) {
    return a->GetX() * b->GetX() + a->GetY() * b->GetY();
}

bool CMath::isXYZ(CVertex* a, CVertex* b) {
    if ((a->GetX() == b->GetX()) && (a->GetY() == b->GetY()) && (a->GetZ() == b->GetZ()))
        return true;
    return false;
}

float CMath::calcAngle(CVector* a, CVector* b) {
    // •ª•ê‚Ì“àÏ
    float innerProduct = calcInnerProduct(a, b);
    // •ªŽq‚ÌŠOÏ
    float crossProduct = calcCrossProduct(a, b);

    return atan2(absFloat(crossProduct), innerProduct);
}

float CMath::calcAngleByShape(CShape* currentShape, CVertex* vertex) {
    float result=0.0f;
    float tanAngle;
    CVector* a = new CVector();
    CVector* b = new CVector();

    for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
        a->SetByVertex(vertex, current);
        b->SetByVertex(vertex, current->GetNext());
        tanAngle = calcAngle(a, b);

        if (calcCrossProduct(a, b) > 0) result += tanAngle;
        else result -= tanAngle;
    }
    delete a, b;
    return absFloat(result);
}

float CMath::absFloat(float value) {
    if (value < 0) return value * (-1);
    return value;
}

float CMath::calcPointLineDistance(CVertex* lineStart, CVertex* lineEnd, CVertex* vertex) {
    CVector* a = new CVector(lineStart, lineEnd);
    CVector* b = new CVector(lineStart, vertex);

    float distance = calcVectorDistance(b) * calcSinTheta(a, b);

    delete a, b;

    return distance;
}

float CMath::calcSinTheta(CVector* a, CVector* b) {
    // •ªŽq
    float crossProduct = absFloat(calcCrossProduct(a, b));
    // •ª•ê
    float vectorDistance = calcVectorDistance(a) * calcVectorDistance(b);

    return crossProduct / vectorDistance;
}

float CMath::calcVectorDistance(CVector* a) {
    return sqrt(pow(a->GetX(),2)+pow(a->GetY(),2));
}

void CMath::calcMovementByVertex(CVertex* beforVertex, CVertex* afterVertex, float(&result)[2]) {
    result[0] = afterVertex->GetX() - beforVertex->GetX();
    result[1] = afterVertex->GetY() - beforVertex->GetY();
}
