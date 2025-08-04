package bankaccount;

public class Account extends SuperAccount{

	private Integer balance;
	private Person test;
	private AccountType type;

	public Account(Integer balance, Person test, AccountType type) {
		this.setBalance(balance);
		this.setTest(test);
		this.setType(type);
	}

	public Integer getBalance() {
		return this.balance;
	}

	public void setBalance(Integer balance) {
		this.balance = balance;
	}

	public Person getTest() {
		return this.test;
	}

	public void setTest(Person test) {
		this.test = test;
	}

	public AccountType getType() {
		return this.type;
	}

	public void setType(AccountType type) {
		this.type = type;
	}

}
