/* -------------------------------------------------------------------------- *
 *                                OpenMMAmoeba                                *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2010 Stanford University and the Authors.           *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "../../../tests/AssertionUtilities.h"
#include "openmm/AmoebaHarmonicInPlaneAngleForce.h"
#include "openmm/serialization/XmlSerializer.h"
#include <iostream>
#include <sstream>

using namespace OpenMM;
using namespace std;

void testSerialization() {
    // Create a Force.

    AmoebaHarmonicInPlaneAngleForce force1;

    force1.setAmoebaGlobalHarmonicInPlaneAngleCubic( 12.3 );
    force1.setAmoebaGlobalHarmonicInPlaneAngleQuartic( 98.7 );
    force1.setAmoebaGlobalHarmonicInPlaneAnglePentic( 91.7 );
    force1.setAmoebaGlobalHarmonicInPlaneAngleSextic( 93.7 );

    force1.addAngle(0, 1, 3, 4, 1.0, 2.0);
    force1.addAngle(0, 2, 3, 5, 2.0, 2.1);
    force1.addAngle(2, 3, 5, 6, 3.0, 2.2);
    force1.addAngle(5, 1, 8, 8, 4.0, 2.3);

    // Serialize and then deserialize it.

    stringstream buffer;
    XmlSerializer::serialize<AmoebaHarmonicInPlaneAngleForce>(&force1, "Force", buffer);
    AmoebaHarmonicInPlaneAngleForce* copy = XmlSerializer::deserialize<AmoebaHarmonicInPlaneAngleForce>(buffer);

    // Compare the two forces to see if they are identical.  
    AmoebaHarmonicInPlaneAngleForce& force2 = *copy;

    ASSERT_EQUAL(force1.getAmoebaGlobalHarmonicInPlaneAngleCubic(),    force2.getAmoebaGlobalHarmonicInPlaneAngleCubic());
    ASSERT_EQUAL(force1.getAmoebaGlobalHarmonicInPlaneAngleQuartic(),  force2.getAmoebaGlobalHarmonicInPlaneAngleQuartic());
    ASSERT_EQUAL(force1.getAmoebaGlobalHarmonicInPlaneAnglePentic(),   force2.getAmoebaGlobalHarmonicInPlaneAnglePentic());
    ASSERT_EQUAL(force1.getAmoebaGlobalHarmonicInPlaneAngleSextic(),   force2.getAmoebaGlobalHarmonicInPlaneAngleSextic());
    ASSERT_EQUAL(force1.getNumAngles(),                                force2.getNumAngles());

    for ( unsigned int ii = 0; ii < force1.getNumAngles(); ii++) {
        int a1, a2, a3, a4, b1, b2, b3, b4;
        double da, db, ka, kb;
        force1.getAngleParameters(ii, a1, a2, a3, a4, da, ka);
        force2.getAngleParameters(ii, b1, b2, b3, b4, db, kb);
        ASSERT_EQUAL(a1, b1);
        ASSERT_EQUAL(a2, b2);
        ASSERT_EQUAL(a3, b3);
        ASSERT_EQUAL(a4, b4);
        ASSERT_EQUAL(da, db);
        ASSERT_EQUAL(ka, kb);
    }
}

int main() {
    try {
        testSerialization();
    }
    catch(const exception& e) {
        cout << "exception: " << e.what() << endl;
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
