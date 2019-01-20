#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
int numOfNeurons = atoi(argv[2]);
char check = 0;
int coupling = atoi(argv[1]);
int i = 1;
char* fileName = argv[3];

FILE *f;
f = fopen(fileName, "w");

fprintf(f,"{\"configuration\": {\n\"solver\": {\n\"startTime\": 0,\n\"endTime\": 60,\n\"solver\": \"runge_kutta_dopri5\",\n\"absoluteError\": 1e-6,\n\"relativeError\": 1e-6,\n\"useLUT\": false\n},\n\"neurons\": {\n");


while(i<=numOfNeurons){

	//Ring of Neurons
	if(coupling <= 0){ 
	fprintf(f," \"N%d\": {\n\"neuronType\": \"neuronType1\",\n\"iVoltage\": -50e-3,\n\"imk2\": 0.0619, \n\"imp\": 0.1874, \n\"imna\": 0.0408,\n\"ihna\": 0.9999,\n\"imcaf\": 0.0488,\n\"ihcaf\": 0.2835,\n\"imcas\": 0.0888,\n\"ihcas\": 0.5189,\n\"imk1\": 0.0127,\n\"ihk1\": 0.9439,\n\"imka\": 0.264882,\n\"ihka\": 0.1724,\n\"imkf\": 0.0436,\n\"imh\":0.563,\n\"inputCurrent\": \"none\",\n\"synapses\": {\n\"synapseType1\": [\"N%d\"]\n}\n},\n",i,i+1);
	}

	//Coupled random neuron configuration
	else{
        if(i==1){
        		fprintf(f," \"N%d\": {\n\"neuronType\": \"neuronType1\",\n\"iVoltage\": -39.4e-3,\n\"imk2\": 0.23, \n\"imp\": 0.45, \n\"imna\": 0.17,\n\"ihna\": 0.9999,\n\"imcaf\": 0.97,\n\"ihcaf\": 0.005,\n\"imcas\": 0.946,\n\"ihcas\": 0.086,\n\"imk1\": 0.061,\n\"ihk1\": 0.710,\n\"imka\": 0.612,\n\"ihka\": 0.026,\n\"imkf\": 0.142,\n\"imh\":0.098,\n\"inputCurrent\": \"none\",\n\"synapses\": {\n",i);
        }
        else{
		fprintf(f," \"N%d\": {\n\"neuronType\": \"neuronType1\",\n\"iVoltage\": -50e-3,\n\"imk2\": 0.0619, \n\"imp\": 0.1874, \n\"imna\": 0.0408,\n\"ihna\": 0.9999,\n\"imcaf\": 0.0488,\n\"ihcaf\": 0.2835,\n\"imcas\": 0.0888,\n\"ihcas\": 0.5189,\n\"imk1\": 0.0127,\n\"ihk1\": 0.9439,\n\"imka\": 0.264882,\n\"ihka\": 0.1724,\n\"imkf\": 0.0436,\n\"imh\":0.563,\n\"inputCurrent\": \"none\",\n\"synapses\": {\n",i);
        }
        int j;
        fprintf(f,"\"synapseType1\": [");
        
        int connections = (numOfNeurons -1)*coupling/100;
        if(connections <=0) connections = 1;
        int space = (numOfNeurons -1)/connections;
        int pos = space;
        int firstWrite = 1;
        //printf("test %d\n", connections);
        for(j = i+1; j<=numOfNeurons+i; j++){
            if(pos==space){
                pos =1;
                connections--;
                if(j>numOfNeurons){
                    //printf("created %d to %d\n",i,j-numOfNeurons);
                    if(firstWrite){
                        firstWrite=0;
                    }else{
                        fprintf(f,",");
                    }
                    fprintf(f,"\"N%d\"",j-numOfNeurons);
                }else{
                    if(firstWrite){
                        firstWrite=0;
                    }else{
                        fprintf(f,",");
                    }
                    //printf("created %d to %d\n",i,j);
                    fprintf(f,"\"N%d\"",j);
                }
                if(connections<=0) break;
            }else{
                pos++;
            }
		}
        if(i<=numOfNeurons-1){
            fprintf(f,"]\n}\n},\n ");
        }else{
            fprintf(f,"]\n}\n}\n ");
        }
	}
i++;
}
fprintf(f,"\n},\n\"neuronParameters\": {\n\"neuronType1\": {\n\"gbarna\":     200.0e-9,\n\"gbarna_dev\": 0,\n\"gbarp\":      7.0e-9,\n\"gbarp_dev\":  0,\n\"gbarcaf\":    5.0e-9,\n\"gbarcaf_dev\":0,\n\"gbarcas\":    3.2e-9,\n\"gbarcas_dev\":0,\n\"gbark1\":     100.0e-9,\n\"gbark1_dev\": 0,\n\"gbark2\":     80.0e-9,\n\"gbark2_dev\": 0,\n\"gbarka\":     80.0e-9,\n\"gbarka_dev\": 0,\n\"gbarkf\":     0.0e-9,\n\"gbarkf_dev\": 0,\n\"gbarh\":      4.0e-9,\n\"gbarh_dev\":  0,\n\"gbarl\":      8.0e-9,\n\"gbarl_dev\":  0,\n\"ena\":        0.045,\n\"ena_dev\":    0,\n\"eca\":        0.135,\n\"eca_dev\":    0,\n\"ek\":         -0.07,\n\"ek_dev\":     0,\n\"eh\":         -0.021,\n\"eh_dev\":     0,\n\"el\":         -0.06,\n\"el_dev\":     0,\n\"capacitance\":      5.0e-10,\n\"capacitance_dev\":  0\n}\n},\n\"synapseParameters\": {\n\"synapseType1\": {\n\"gbarsyng\":     30.0e-9,\n\"gbarsyng_dev\": 0,\n\"gbarsyns\":     60.0e-9,\n\"gbarsyns_dev\": 0,\n\"esyn\":         -0.0625,\n\"esyn_dev\":     0,\n\"buffering\":    10.0,\n\"buffering_dev\":0,\n\"h0\":           600.0e3,\n\"h0_dev\":       0,\n\"thresholdV\":   -0.1e-3,\n\"thresholdV_dev\":0,\n\"tauDecay\":     0.011,\n\"tauDecay_dev\": 0,\n\"tauRise\":      0.002,\n\"tauRise_dev\":  0,\n\"cGraded\":      1.0e-32,\n\"cGraded_dev\":  0,\n\"iA\":           0,\n\"iP\":           0,\n\"iM\":           1,\n\"ig\":           0,\n\"ih\":           0\n}\n},\n\"inputCurrents\": {\n\"none\": {\n\"initialCurrent\": 0.0,\n\"steps\": []\n},\n\"step1\":{\n\"initialCurrent\": 0.0,\n\"steps\": [\n{\"time\": 10,\n\"delta\": 0.001\n}\n]\n}\n}\n}\n}\n");
fclose(f);
}
