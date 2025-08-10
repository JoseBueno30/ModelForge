package bankaccount;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Account extends SuperAccount{

	private Integer balance;
	private Person test;
	private AccountType type;
	private Bank bank;
	private Person owner;
	private List<Person> users;

	public Account(Integer balance, Person test, AccountType type, Bank bank, Person owner) {
		this.setBalance(balance);
		this.setTest(test);
		this.setType(type);
		this.setBank(bank);
		this.setOwner(owner);
		this.users = new ArrayList<Person>();
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

	public Bank getBank() {
		return this.bank;
	}

	public void setBank(Bank bank) {
		if (bank == null) {
			throw new IllegalArgumentException("bank must not be null.");
		}
		this.bank = bank;
	}

	public Person getOwner() {
		return this.owner;
	}

	public void setOwner(Person owner) {
		if (owner == null) {
			throw new IllegalArgumentException("owner must not be null.");
		}
		this.owner = owner;
	}

	public List<Person> getUsers() {
		return Collections.unmodifiableList(this.users);
	}

	public void addUser(Person element) {
		this.users.add(element);
	}

	public void removeUser(Person element) {
		this.users.remove(element);
	}

}
