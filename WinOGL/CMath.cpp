#include "pch.h"
#include "CMath.h"

float CMath::calcDistance(CVertex* vertex1, CVertex* vertex2) {
    return sqrt(pow((vertex2->GetX()-vertex1->GetX()),2)+ pow((vertex2->GetY() - vertex1->GetY()), 2));
}

float CMath::calcCrossProduct(CVector* a, CVector* b) {
    return a->GetX() * b->GetY() - a->GetY() * b->GetX();
}

bool CMath::isXYZ(CVertex* a, CVertex* b) {
    if ((a->GetX() == b->GetX()) && (a->GetY() == b->GetY()) && (a->GetZ() == b->GetZ()))
        return true;
    return false;
}
