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
    // •ª•ê‚ÌŠOÏ
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
    return result;
}

float CMath::absFloat(float value) {
    if (value < 0) return value * (-1);
    return value;
}
