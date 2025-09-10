#include <iostream>
#include<cmath>
using namespace std;

void shearStress(double SF, int width, int depth, int y);

int width, depth, y;
int shapeOfBeam, rectangle,circle,stressSelected;
double SF,BendingStress,MoI;
bool beam, center, typeofload, all;
int BMGiven, IGiven, sigmaGiven, yGiven, loadGiven, spanGiven;
long bendingMoment;

int main() {
    cout<<"What you want to calculate?"<<endl;
    cout<<"1. Shear Stress"<<endl;
    cout<<"2. Bending Stress"<<endl;
    cout<<"Enter 1 or 2: ";
    cin>>stressSelected;
    if (stressSelected==2){
        cout<<"Bending Stress Calculator is under development."<<endl;
        cout << "What is given?" << endl;
       

        cout << "1. Bending Moment?" << endl;
        cout << "Enter 1:Yes or 0:No : "<<endl;
        cin >> BMGiven;
        if (BMGiven==1){
            cout<<"Enter Bending Moment (M) in kNm: ";
            cin>>bendingMoment;
        } else {
            cout<<"Enter given data to calculate Bending Moment."<<endl;
            cout<< "Enter type of beam enter 1 for simply supported, 0 for cantilever: ";
            cin>>beam;
            double load, length;
            double a, b;

            if (beam) {  // Simply supported beam
                cout << "Type of load enter 1 for point load, 0 for UDL: ";
                cin >> typeofload;

                if (typeofload) {  // Point Load
                    cout << "Enter load (W) in kN: ";
                    cin >> load;
                    cout << "Enter Span of Beam (L) in m: ";
                    cin >> length;
                    spanGiven=length;
                    cout << "Is the load at center? Enter 1 for yes, 0 for no: ";
                    cin >> center;

                    if (center) {
                        bendingMoment = (load * spanGiven) / 4;  // Max bending moment at center
                    }
                    else {
                        cout << "Enter distance 'a' from left support to load in m: ";
                        cin >> a;
                        b = length - a;
                        bendingMoment = (load * a * b) / length;  // Bending moment at distance 'a'
                    }
                }
                else {  // UDL
                    cout << "Enter load (W) in kN/m: ";
                    cin >> load;
                    cout << "Is the load covering entire span? Enter 1 for yes, 0 for no: ";
                    cin >> all;

                    if (all) {
                        length=spanGiven;
                        bendingMoment = (load * spanGiven * spanGiven) / 8;  // Max bending moment at center for full UDL
                    }
                    else {
                        cout << "Enter distance 'a' from left support to start of load in m: ";
                        cin >> a;
                        cout << "Enter distance 'b' from right support to end of load in m: ";
                        cin >> b;
                        // Shear at left support for partial UDL: Load * (length - b) * (length - b)/length
                        double loadLength = length - a - b;
                        bendingMoment = (load * loadLength * (length - b) * (length - b)) / (2 * length);
                    }
                }
            }
            else {  // Cantilever beam
                cout << "Enter Span of Beam (L) in m: ";
                cin >> length;
                cout << "Type of load enter 1 for point load, 0 for UDL: ";
                cin >> typeofload;

                if (typeofload) {  // Point Load
                    cout << "Enter load (W) in kN: ";
                    cin >> load;

                    cout << "Is the load at free end? Enter 1 for yes, 0 for no: ";
                    cin >> center;

                    if (center) {
                        a = length ;
                    }
                    else {
                        cout << "Enter distance 'a' from fixed support to load in m: ";
                        cin >> a;
                    }
                    bendingMoment = load * a;  // Max bending moment at fixed end for cantilever
                }
                else {  // UDL
                    cout << "Enter load (W) in kN/m: ";
                    cin >> load;

                    cout << "Is the load covering entire span? Enter 1 for yes, 0 for no: ";
                    cin >> all;

                    if (all) {
                        bendingMoment = (load * length * length) / 2;  // Max bending moment at fixed end for full UDL
                    }
                    else {
                        cout << "Enter distance 'a' from fixed support to start of load in m: ";
                        cin >> a;
                        cout << "Enter distance 'b' from free end to end of load in m: ";
                        cin >> b;
                        double loadLength = length - a - b;
                        bendingMoment = load * loadLength * (length - b) / 2;
                    }
                }
            }
        }

        cout << "2. Moment of Inertia (I)? :"<<endl ;
        cout << "Enter 1:Yes or 0:No : "<<endl ;
        cin >> IGiven;
        if (IGiven==0){
            cout << "Select shape of cross-section"<<endl;
            cout << "1. Rectangle" << endl;
            cout << "2. Circle" << endl;
            cout << "Enter 1 or 2: ";
            cin >> shapeOfBeam;

            if (shapeOfBeam == 1){
                cout << "You have selected Rectangle" << endl;
                cout << "---------------------------------" << endl;
                cout << "Enter width of rectangle: ";
                cin >> width;
                cout << "Enter depth of rectangle: ";
                cin >> depth;
                MoI = (width * pow(depth,3)) / 12.0;}
      } 
        
      
        cout << "3. Distance from neutral axis to point where bending stress is to be calculated (y)? :";
        cout << "Enter 1:Yes or 0:For Ymax : ";
        cin >> yGiven;
        if (yGiven==1){
            cin >> yGiven;
        } else {
            yGiven=depth/2;
            cout<< "y is taken as "<<yGiven<<endl;
        }
      
        cout << "4. Bending Stress (σ)? :";
        cout << "Enter 1:Yes or 0:No : ";
        cin >> sigmaGiven;
        if (sigmaGiven==1){
            cin >> BendingStress;
            cout<< "Bending Stress is given as "<<BendingStress<<endl;
        } else {
            cout << "---------------------------------" << endl;
            cout<< "Calculating Bending Stress..."<<endl;
            cout << "Given Bending Moment (M) is "<<(bendingMoment*1000000)<<" Nmm"<<endl;
            cout << "Given Moment of Inertia (I) is "<<MoI<<" mm^4"<<endl;
            cout << "Given distance y is "<<yGiven<<" mm"<<endl;
            BendingStress = ((bendingMoment*1000000 )* yGiven) / MoI;
            cout<< "Calculated Bending Stress is "<<BendingStress<<" N/mm^2"<<endl;
        }
    
    } else if (stressSelected==1){
        cout<<"You have selected Shear Stress calculation."<<endl;
        cout << "Shear Stress Calculator" << endl;
        cout << "---------------------------------" << endl;
        cout << "Select the cross-section shape (1 for Rectangle, 0 for Circle): ";
        cin >> shapeOfBeam;

        if (shapeOfBeam == 1){
            cout << "You have selected Rectangle" << endl;
            cout << "---------------------------------" << endl;
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

            // Call shearStress with calculated shear force and geometry
            shearStress(SF, width, depth, y);

        }
    }
    


    
    return 0;
}

// Function to calculate and print shear stress
void shearStress(double SF, int width, int depth, int y) {

    cout << "Calculated Shear Force: " << SF << " kN" << endl;

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
    cout << "Shear Stress is: " << shearStress << " N/mm^2" << endl;

	cout << "---------------------------------" << endl;
}
