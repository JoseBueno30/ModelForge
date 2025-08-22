package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Productos_Pedido{

	private Integer cantidad;
	private List<Pedido> pedido;
	private List<Producto> producto;

	public Productos_Pedido(Integer cantidad) {
		this.setCantidad(cantidad);
		this.pedido = new ArrayList<Pedido>();
		this.producto = new ArrayList<Producto>();
	}

	public Integer getCantidad() {
		return this.cantidad;
	}

	public void setCantidad(Integer cantidad) {
				this.cantidad = cantidad;
	}

	public List<Pedido> getPedido() {
		return Collections.unmodifiableList(this.pedido);
	}

	public void addPedido(Pedido element) {
		this.pedido.add(element);
		element.addProductos_Pedido(this);
	}

	public void removePedido(Pedido element) {
		this.pedido.remove(element);
		element.removeProductos_Pedido(this);
;
	}

	public List<Producto> getProducto() {
		return Collections.unmodifiableList(this.producto);
	}

	public void addProducto(Producto element) {
		this.producto.add(element);
		element.addProductos_Pedido(this);
	}

	public void removeProducto(Producto element) {
		this.producto.remove(element);
		element.removeProductos_Pedido(this);
;
	}

}
