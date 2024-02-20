//compare the true positive rate and the false positive rate and outputs the best one 

//cmath and iostream library used
#include <iostream>
#include <cmath>
//standard namespace is used
using namespace std;

int main() {
    //initialize variables that will be used for calculations
    float TPR = 0.0f;
    float FPR = 0.0f;
    float score = 0.0f;
    //initialize variable to store best test result
    float bestTest = 0.0f;
    //initialize variable to keep track of the amounts of scores
    int i = 0;  
    int test = 0;
    
    //will loop program while test case is true
    do {  
    i++; //increases each comparison by 1 after each loop
    
    //ask user input for true postitive rate
    cout<<"Please enter the diagnostic test's true positive rate: "; //ask user input for true postitive rate
    cin>>TPR;
        
        do { //do while loop that will trigger if user inputs an invalid case
            if (!cin.good()) { //will execute when the wrong input is entered
                cout<<"Warning: invalid input to true positive rate. Please enter a numeric input."<<endl;
                cin.clear(); //clears the input to prevent unwanted errors
                cin.ignore(100, '\n');
                cout<<"Please enter the diagnostic test's true positive rate: ";
                cin>>TPR;
            }
            else if (TPR>1) { //will execute when the input is greater then 1
                cout<<"Warning: invalid input to true positive rate. Please enter an input <=1."<<endl;
                cin.clear(); 
                cin.ignore(100, '\n');
                cout<<"Please enter the diagnostic test's true positive rate: "; //asks for user input again
                cin>>TPR;
            }    
        } while (!cin.good()||TPR>1);  //loops if input is greater then 1 or if invalid input
    
        cout<<"Please enter the diagnostic test's false positive rate: ";
        cin>>FPR;

        do  { //do while loop that will trigger if user inputs an invalid case        
            if (!cin.good()) { //will execute when the wrong input is entered
                cout<<"Warning: invalid input to false positive rate. Please enter a numeric input."<<endl;
                cin.clear();
                cin.ignore(100, '\n');
                cout<<"Please enter the diagnostic test's false positive rate: ";
                cin>>FPR;
            }
            else if (FPR>1) { //will execute when the input is greater then 1
                cout<<"Warning: invalid input to true false rate. Please enter an input <=1."<<endl;
                cin.clear();
                cin.ignore(100, '\n');  
                cout<<"Please enter the diagnostic test's false positive rate: ";
                cin>>FPR;
            }
        } while (!cin.good()||FPR>1); //loops if input is greater then 1 or if invalid input

        //if TPR or FPR is negative, it will initialize the negative float as 0
        if (TPR<0 && FPR>=0) {
            TPR = 0.0f;
        }
        else if (FPR<0 && TPR>=0) {
            FPR = 0.0f;
        }

        //calculates the score for the test and outputs the results only if TPR and FPR are greater then or equal to 0
        if (TPR>=0 && FPR>=0) {
            score = 1 - sqrt(pow(FPR,2)+pow(1-TPR,2));
            cout<<"The score for diagnostic test "<<i<<" is "<<score<<endl;
        }
        
        //checks if current score is better then previous best score
        if (score>bestTest) {
            bestTest = score;  //if current score is better it becomes the new best test
            test = i;  //if current score is better, stores the number for the test (i.e if the best test is test 1, stores 1 for the number)
        }

    } while (TPR,FPR>=0);  //will loop while TPR and FPR are greater then or equal to 0

    //outputs when both TPR and FPR are negatives
    cout<<"Exiting program"<<endl;
    //outputs which is the best test and its score
    cout<<"The best test is test "<<test<<" with a score of "<<bestTest<<endl;

    return 0;
}