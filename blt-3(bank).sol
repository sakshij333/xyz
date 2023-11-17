pragma solidity ^0.8.0;

contract SimpleBank {
    address public owner;
    uint256 public balance;

    constructor() public {
        owner = msg.sender;
        balance = 0;
    }

    function deposit(uint256 amount) public {
        require(msg.sender == owner, "Only the owner can deposit money");
        balance += amount;
    }

    function withdraw(uint256 amount) public {
        require(msg.sender == owner, "Only the owner can withdraw money");
        require(amount <= balance, "Insufficient balance");
        balance -= amount;
    }

    function getBalance() public returns (uint256) {
        return balance;
    }
}
