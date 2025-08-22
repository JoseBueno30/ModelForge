package library;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Library{

	private Integer code;
	private String dir;
	private String mail;
	private String name;
	private Integer tel;
	private List<Item> item;
	private List<User> user;

	public Library(Integer code, String dir, String mail, String name, Integer tel) {
		this.setCode(code);
		this.setDir(dir);
		this.setMail(mail);
		this.setName(name);
		this.setTel(tel);
		this.item = new ArrayList<Item>();
		this.user = new ArrayList<User>();
	}

	public Integer getCode() {
		return this.code;
	}

	public void setCode(Integer code) {
				this.code = code;
	}

	public String getDir() {
		return this.dir;
	}

	public void setDir(String dir) {
				this.dir = dir;
	}

	public String getMail() {
		return this.mail;
	}

	public void setMail(String mail) {
				this.mail = mail;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
				this.name = name;
	}

	public Integer getTel() {
		return this.tel;
	}

	public void setTel(Integer tel) {
				this.tel = tel;
	}

	public List<Item> getItem() {
		return Collections.unmodifiableList(this.item);
	}

	public void addItem(Item element) {
		this.item.add(element);
	}

	public void removeItem(Item element) {
		this.item.remove(element);
	}

	public List<User> getUser() {
		return Collections.unmodifiableList(this.user);
	}

	public void addUser(User element) {
		this.user.add(element);
	}

	public void removeUser(User element) {
		this.user.remove(element);
	}

}
