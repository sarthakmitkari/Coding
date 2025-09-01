#include <iostream>
using namespace std;


void shearStress(double SF, int width, int depth, int y);

int width, depth, y;
double SF;
bool beam, center, typeofload, all;

int main() {
    cout << "Enter width of rectangle: ";
    cin >> width;

    cout << "Enter depth of rectangle: ";
    cin >> depth;

    cout << "Enter the distance y from neutral axis to point where shear stress is to be calculated: ";
    cin >> y;

	cout << "Enter Shear Force (if known, else enter 0): ";
	cin >> SF;
    if (SF != 0) {
        shearStress(SF, width, depth, y);
        return 0;
	}

    cout << "Type of beam enter 1 for simply supported, 0 for cantilever: ";
    cin >> beam;

    double load, length;
    double a, b;

    cout << "Type of load enter 1 for point load, 0 for UDL: ";
    cin >> typeofload;

    if (beam) {  // Simply supported beam
        cout << "Enter Span of Beam (L) in m: ";
        cin >> length;

        if (typeofload) {  // Point Load
            cout << "Enter load (W) in kN: ";
            cin >> load;

            cout << "Is the load at center? Enter 1 for yes, 0 for no: ";
            cin >> center;

            if (center) {
                SF = load / 2.0;  // Shear force at supports
            }
            else {
                cout << "Enter distance 'a' from left support to load in m: ";
                cin >> a;
                b = length - a;
                SF = (load * b) / length;  // Shear force at left support
            }
        }
        else {  // UDL
            cout << "Enter load (W) in kN/m: ";
            cin >> load;
            cout << "Is the load covering entire span? Enter 1 for yes, 0 for no: ";
            cin >> all;

            if (all) {
                SF = (load * length) / 2.0;  // Shear force at supports for full UDL
            }
            else {
                cout << "Enter distance 'a' from left support to start of load in m: ";
                cin >> a;
                cout << "Enter distance 'b' from right support to end of load in m: ";
                cin >> b;
                // Shear at left support for partial UDL: Load * (length - b) * (length - b)/length
                double loadLength = length - a - b;
                SF = load * loadLength * (length - b) / length;
            }
        }
    }
    else {  // Cantilever beam
        cout << "Enter Span of Beam (L) in m: ";
        cin >> length;

        if (typeofload) {  // Point Load
            cout << "Enter load (W) in kN: ";
            cin >> load;

            cout << "Is the load at center? Enter 1 for yes, 0 for no: ";
            cin >> center;

            if (center) {
                a = length / 2.0;
            }
            else {
                cout << "Enter distance 'a' from fixed support to load in m: ";
                cin >> a;
            }
            SF = load;  // Shear force at the fixed end equals the load for cantilever
        }
        else {  // UDL
            cout << "Enter load (W) in kN/m: ";
            cin >> load;

            cout << "Is the load covering entire span? Enter 1 for yes, 0 for no: ";
            cin >> all;

            if (all) {
                SF = load * length;
            }
            else {
                cout << "Enter distance 'a' from fixed support to start of load in m: ";
                cin >> a;
                cout << "Enter distance 'b' from free end to end of load in m: ";
                cin >> b;
                double loadLength = length - a - b;
                SF = load * loadLength;
            }
        }
    }

    cout << "Calculated Shear Force: " << SF << " kN" << endl;

    // Call shearStress with calculated shear force and geometry
    shearStress(SF, width, depth, y);

    return 0;
}

// Function to calculate and print shear stress
void shearStress(double SF, int width, int depth, int y) {

	cout << "---------------------------------" << endl;

    // Calculate area of sheared part (As)
    double As = width * ((depth / 2.0) - y);

    // Calculate moment of inertia (I)
    double I = (width * (depth * depth * depth)) / 12.0;

    // Calculate Ybar
    double Ybar = ((depth / 2.0 - y) / 2.0)+y;

    cout << "Area of sheared part is: " << As << endl;
    cout << "Moment of Inertia is: " << I << endl;
    cout << "(Ybar) Distance from neutral axis to centroid is: " << Ybar << endl;

    double shearStress = (SF * As * Ybar) / (I * width);
    cout << "Shear Stress is: " << shearStress << " (units consistent with inputs)" << endl;

	cout << "---------------------------------" << endl;
}
