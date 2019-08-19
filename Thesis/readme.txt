Learning to Solve the Game 2048 Using Temporal Difference Learning Source Code

The source code included is mainly for the TD(0), the simplest Temporal Difference Learning Method. Included near the end of the source code are commented blocks of classes and functions to add and/or replace in the TD(0) source code. Each block of comments corresponds to the different methods: TDL, TCL, Delayed TDL, Delayed TCL.

Simply compile and run to gather results.

-Output-
The source code included outputs two .txt files that includes a code for graphing the data via MATLAB. One file for graphing the average score over the number of games and one for graphing the win rate over the number of games. The output files are created and cleaned in lines 101 and 103 and are again used for writing in lines 128 - 136.

-Editing Parameters-
1) The number of games can be edited to how many the user wants in line 106 by changing the value found under the condition statement.
2) The initial value of alpha in the TD(0) method can be changed by changing the value in line 357.

-Commented Blocks-
A) Lines 616 - 715 includes classes and functions for the TDL method.
	--Editing Parameters--
	1) The initial value of alpha can be changed in line 647.

B) Lines 717 - 871 includes classes and functions for the TCL method.
	--Editing Parameters--
	1) The initial value of beta can be changed in line 764.
	2) The initial value of alpha can be changed in line 869. Take note that you need to change the value of tuple[i].alpha found in line 846 to the same value.
	
C) Lines 873 - 957 includes classes and functions for the Delayed TDL method.
		The same classes and functions from the TDL method must also be used and the parameters that can be edited are the same.
		
D) Lines 959 - 1043 includes classes and functions for the Delayed TCL method.
		The same classes and functions from the TCL method must also be used and the parameters that can be edited are the same.