//4. Write a program in solidity to create Student data. Use the following constructs:
//Structures
//Arrays
//Fallback
//Deploy this as smart contract on Ethereum and Observe the transaction fee and Gas values.
pragma solidity 0.8.0;

// Build the Contract
contract MarksManagmtSys
{
	// Create a structure for
	// student details
	   uint[] data; 
    
    // Declaring state variable
  //  uint8 j = 0;
    uint k;
  
	struct Student
	{
		int ID;
		string fName;
		string lName;
		int marks;
	
	}
	
    event Log(string func, address sender, uint value);
	address owner;
	int public stdCount = 0;
	mapping(int => Student) public stdRecords;

	modifier onlyOwner
	{
		require(owner == msg.sender);
		_;
	}
	constructor()
	{
		owner=msg.sender;
	}

	// Create a function to add
	// the new records

	function addNewRecords(int _ID,
						string memory _fName,
						string memory _lName,
						int _marks
						) public onlyOwner				
	{
		// Increase the count by 1
		stdCount = stdCount + 1;
     
		// Fetch the student details
		// with the help of stdCount
		stdRecords[stdCount] = Student(_ID, _fName,
									_lName, 
									_marks
									);
	
	}
	function percentage(uint k) public returns(uint[] memory){
   // do{
     //   j++;
      data.push(k);
    // }
     //while(j < 5) ;
     return data;
    }
	
	// Create a function to add bonus marks
	function bonusMarks(int _bonus) public onlyOwner
	{
		stdRecords[stdCount].marks =
					stdRecords[stdCount].marks + _bonus;

	}
	fallback() external payable 
	{
		emit Log("fallback", msg.sender, msg.value);
	}
	receive() external payable 
	{
		emit Log("receive", msg.sender, msg.value);
	}
}


