package library;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Item{

	private String author;
	private String genre;
	private Integer numPages;
	private String title;
	private List<Loan> loan;
	private List<Library> owner;

	public Item(String author, String genre, Integer numPages, String title) {
		this.setAuthor(author);
		this.setGenre(genre);
		this.setNumPages(numPages);
		this.setTitle(title);
		this.loan = new ArrayList<Loan>();
		this.owner = new ArrayList<Library>();
	}

	public String getAuthor() {
		return this.author;
	}

	public void setAuthor(String author) {
				this.author = author;
	}

	public String getGenre() {
		return this.genre;
	}

	public void setGenre(String genre) {
				this.genre = genre;
	}

	public Integer getNumPages() {
		return this.numPages;
	}

	public void setNumPages(Integer numPages) {
		//self.numPages > 0
		this.numPages = numPages;
	}

	public String getTitle() {
		return this.title;
	}

	public void setTitle(String title) {
				this.title = title;
	}

	public List<Loan> getLoan() {
		return Collections.unmodifiableList(this.loan);
	}

	public void addLoan(Loan element) {
		this.loan.add(element);
	}

	public void removeLoan(Loan element) {
		this.loan.remove(element);
	}

	public List<Library> getOwner() {
		return Collections.unmodifiableList(this.owner);
	}

	public void addOwner(Library element) {
		this.owner.add(element);
	}

	public void removeOwner(Library element) {
		this.owner.remove(element);
	}

}
