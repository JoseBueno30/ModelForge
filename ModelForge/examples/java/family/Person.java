package family;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Person{

	private Integer age;
	private String name;
	private String surname1;
	private String surname2;
	private List<Person> brother1;
	private List<Person> brother2;
	private List<Person> childf;
	private List<Person> childm;
	private List<Person> cousin1;
	private List<Person> cousin2;
	private Person father;
	private Person mother;
	private List<Person> nephew;
	private List<Person> uncle;

	public Person(Integer age, String name, String surname1, String surname2, Person father, Person mother) {
		this.setAge(age);
		this.setName(name);
		this.setSurname1(surname1);
		this.setSurname2(surname2);
		this.brother1 = new ArrayList<Person>();
		this.brother2 = new ArrayList<Person>();
		this.childf = new ArrayList<Person>();
		this.childm = new ArrayList<Person>();
		this.cousin1 = new ArrayList<Person>();
		this.cousin2 = new ArrayList<Person>();
		this.setFather(father);
		this.setMother(mother);
		this.nephew = new ArrayList<Person>();
		this.uncle = new ArrayList<Person>();
	}

	public Integer getAge() {
		return this.age;
	}

	public void setAge(Integer age) {
		this.age = age;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSurname1() {
		return this.surname1;
	}

	public void setSurname1(String surname1) {
		this.surname1 = surname1;
	}

	public String getSurname2() {
		return this.surname2;
	}

	public void setSurname2(String surname2) {
		this.surname2 = surname2;
	}

	public List<Person> getBrother1() {
		return Collections.unmodifiableList(this.brother1);
	}

	public void setBrother1(List<Person> brother1) {
		this.brother1 = new ArrayList<Person>(brother1);
	}

	public void addBrother1(Person element) {
		this.brother1.add(element);
	}

	public void removeBrother1(Person element) {
		this.brother1.remove(element);
	}

	public List<Person> getBrother2() {
		return Collections.unmodifiableList(this.brother2);
	}

	public void setBrother2(List<Person> brother2) {
		this.brother2 = new ArrayList<Person>(brother2);
	}

	public void addBrother2(Person element) {
		this.brother2.add(element);
	}

	public void removeBrother2(Person element) {
		this.brother2.remove(element);
	}

	public List<Person> getChildf() {
		return Collections.unmodifiableList(this.childf);
	}

	public void setChildf(List<Person> childf) {
		this.childf = new ArrayList<Person>(childf);
	}

	public void addChildf(Person element) {
		this.childf.add(element);
	}

	public void removeChildf(Person element) {
		this.childf.remove(element);
	}

	public List<Person> getChildm() {
		return Collections.unmodifiableList(this.childm);
	}

	public void setChildm(List<Person> childm) {
		this.childm = new ArrayList<Person>(childm);
	}

	public void addChildm(Person element) {
		this.childm.add(element);
	}

	public void removeChildm(Person element) {
		this.childm.remove(element);
	}

	public List<Person> getCousin1() {
		return Collections.unmodifiableList(this.cousin1);
	}

	public void setCousin1(List<Person> cousin1) {
		this.cousin1 = new ArrayList<Person>(cousin1);
	}

	public void addCousin1(Person element) {
		this.cousin1.add(element);
	}

	public void removeCousin1(Person element) {
		this.cousin1.remove(element);
	}

	public List<Person> getCousin2() {
		return Collections.unmodifiableList(this.cousin2);
	}

	public void setCousin2(List<Person> cousin2) {
		this.cousin2 = new ArrayList<Person>(cousin2);
	}

	public void addCousin2(Person element) {
		this.cousin2.add(element);
	}

	public void removeCousin2(Person element) {
		this.cousin2.remove(element);
	}

	public Person getFather() {
		return this.father;
	}

	public void setFather(Person father) {
		if (father == null) {
			throw new IllegalArgumentException("father must not be null.");
		}
		this.father = father;
	}

	public Person getMother() {
		return this.mother;
	}

	public void setMother(Person mother) {
		if (mother == null) {
			throw new IllegalArgumentException("mother must not be null.");
		}
		this.mother = mother;
	}

	public List<Person> getNephew() {
		return Collections.unmodifiableList(this.nephew);
	}

	public void setNephew(List<Person> nephew) {
		this.nephew = new ArrayList<Person>(nephew);
	}

	public void addNephew(Person element) {
		this.nephew.add(element);
	}

	public void removeNephew(Person element) {
		this.nephew.remove(element);
	}

	public List<Person> getUncle() {
		return Collections.unmodifiableList(this.uncle);
	}

	public void setUncle(List<Person> uncle) {
		this.uncle = new ArrayList<Person>(uncle);
	}

	public void addUncle(Person element) {
		this.uncle.add(element);
	}

	public void removeUncle(Person element) {
		this.uncle.remove(element);
	}

}
