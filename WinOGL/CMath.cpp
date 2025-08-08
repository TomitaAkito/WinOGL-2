#include "pch.h"
#include "CMath.h"

float CMath::calcDistance(CVertex* vertex1, CVertex* vertex2) {
    return sqrt(pow((vertex2->GetX()-vertex1->GetX()),2)+ pow((vertex2->GetY() - vertex1->GetY()), 2));
}
