package library;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Loan{

	private String finishDate;
	private String startDate;
	private List<Item> item;
	private List<User> user;

	// General constraints
	//self.startDate < self.finishDate

	public Loan(String finishDate, String startDate) {
		this.setFinishDate(finishDate);
		this.setStartDate(startDate);
		this.item = new ArrayList<Item>();
		this.user = new ArrayList<User>();
	}

	public String getFinishDate() {
		return this.finishDate;
	}

	public void setFinishDate(String finishDate) {
				this.finishDate = finishDate;
	}

	public String getStartDate() {
		return this.startDate;
	}

	public void setStartDate(String startDate) {
				this.startDate = startDate;
	}

	public List<Item> getItem() {
		return Collections.unmodifiableList(this.item);
	}

	public void addItem(Item element) {
		this.item.add(element);
		element.setLoan(this);
	}

	public void removeItem(Item element) {
		this.item.remove(element);
		element.setLoan(null);
	}

	public List<User> getUser() {
		return Collections.unmodifiableList(this.user);
	}

	public void addUser(User element) {
		this.user.add(element);
		element.setLoan(this);
	}

	public void removeUser(User element) {
		this.user.remove(element);
		element.setLoan(null);
	}

}
