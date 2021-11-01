// package: stylekorean
// file: stylekorean.proto

import * as jspb from "google-protobuf";

export class LoginRequest extends jspb.Message {
  getUsername(): string;
  setUsername(value: string): void;

  getPassword(): string;
  setPassword(value: string): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): LoginRequest.AsObject;
  static toObject(includeInstance: boolean, msg: LoginRequest): LoginRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: LoginRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): LoginRequest;
  static deserializeBinaryFromReader(message: LoginRequest, reader: jspb.BinaryReader): LoginRequest;
}

export namespace LoginRequest {
  export type AsObject = {
    username: string,
    password: string,
  }
}

export class LoginResponse extends jspb.Message {
  getToken(): string;
  setToken(value: string): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): LoginResponse.AsObject;
  static toObject(includeInstance: boolean, msg: LoginResponse): LoginResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: LoginResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): LoginResponse;
  static deserializeBinaryFromReader(message: LoginResponse, reader: jspb.BinaryReader): LoginResponse;
}

export namespace LoginResponse {
  export type AsObject = {
    token: string,
  }
}

export class GetProductFromBarcodeRequest extends jspb.Message {
  getBarcode(): string;
  setBarcode(value: string): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): GetProductFromBarcodeRequest.AsObject;
  static toObject(includeInstance: boolean, msg: GetProductFromBarcodeRequest): GetProductFromBarcodeRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: GetProductFromBarcodeRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): GetProductFromBarcodeRequest;
  static deserializeBinaryFromReader(message: GetProductFromBarcodeRequest, reader: jspb.BinaryReader): GetProductFromBarcodeRequest;
}

export namespace GetProductFromBarcodeRequest {
  export type AsObject = {
    barcode: string,
  }
}

export class GetProductFromBarcodeResponse extends jspb.Message {
  hasProduct(): boolean;
  clearProduct(): void;
  getProduct(): Product | undefined;
  setProduct(value?: Product): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): GetProductFromBarcodeResponse.AsObject;
  static toObject(includeInstance: boolean, msg: GetProductFromBarcodeResponse): GetProductFromBarcodeResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: GetProductFromBarcodeResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): GetProductFromBarcodeResponse;
  static deserializeBinaryFromReader(message: GetProductFromBarcodeResponse, reader: jspb.BinaryReader): GetProductFromBarcodeResponse;
}

export namespace GetProductFromBarcodeResponse {
  export type AsObject = {
    product?: Product.AsObject,
  }
}

export class AddToCartRequest extends jspb.Message {
  getProductid(): number;
  setProductid(value: number): void;

  getQuantity(): number;
  setQuantity(value: number): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): AddToCartRequest.AsObject;
  static toObject(includeInstance: boolean, msg: AddToCartRequest): AddToCartRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: AddToCartRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): AddToCartRequest;
  static deserializeBinaryFromReader(message: AddToCartRequest, reader: jspb.BinaryReader): AddToCartRequest;
}

export namespace AddToCartRequest {
  export type AsObject = {
    productid: number,
    quantity: number,
  }
}

export class AddToCartResponse extends jspb.Message {
  getSuccess(): boolean;
  setSuccess(value: boolean): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): AddToCartResponse.AsObject;
  static toObject(includeInstance: boolean, msg: AddToCartResponse): AddToCartResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: AddToCartResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): AddToCartResponse;
  static deserializeBinaryFromReader(message: AddToCartResponse, reader: jspb.BinaryReader): AddToCartResponse;
}

export namespace AddToCartResponse {
  export type AsObject = {
    success: boolean,
  }
}

export class AddToOrderListRequest extends jspb.Message {
  getProductid(): number;
  setProductid(value: number): void;

  getQuantity(): number;
  setQuantity(value: number): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): AddToOrderListRequest.AsObject;
  static toObject(includeInstance: boolean, msg: AddToOrderListRequest): AddToOrderListRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: AddToOrderListRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): AddToOrderListRequest;
  static deserializeBinaryFromReader(message: AddToOrderListRequest, reader: jspb.BinaryReader): AddToOrderListRequest;
}

export namespace AddToOrderListRequest {
  export type AsObject = {
    productid: number,
    quantity: number,
  }
}

export class AddToOrderListResponse extends jspb.Message {
  getSuccess(): boolean;
  setSuccess(value: boolean): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): AddToOrderListResponse.AsObject;
  static toObject(includeInstance: boolean, msg: AddToOrderListResponse): AddToOrderListResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: AddToOrderListResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): AddToOrderListResponse;
  static deserializeBinaryFromReader(message: AddToOrderListResponse, reader: jspb.BinaryReader): AddToOrderListResponse;
}

export namespace AddToOrderListResponse {
  export type AsObject = {
    success: boolean,
  }
}

export class ListCurrentCartRequest extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): ListCurrentCartRequest.AsObject;
  static toObject(includeInstance: boolean, msg: ListCurrentCartRequest): ListCurrentCartRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: ListCurrentCartRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): ListCurrentCartRequest;
  static deserializeBinaryFromReader(message: ListCurrentCartRequest, reader: jspb.BinaryReader): ListCurrentCartRequest;
}

export namespace ListCurrentCartRequest {
  export type AsObject = {
  }
}

export class ListCurrentCartResponse extends jspb.Message {
  clearProductbrandsList(): void;
  getProductbrandsList(): Array<ProductsByBrand>;
  setProductbrandsList(value: Array<ProductsByBrand>): void;
  addProductbrands(value?: ProductsByBrand, index?: number): ProductsByBrand;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): ListCurrentCartResponse.AsObject;
  static toObject(includeInstance: boolean, msg: ListCurrentCartResponse): ListCurrentCartResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: ListCurrentCartResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): ListCurrentCartResponse;
  static deserializeBinaryFromReader(message: ListCurrentCartResponse, reader: jspb.BinaryReader): ListCurrentCartResponse;
}

export namespace ListCurrentCartResponse {
  export type AsObject = {
    productbrandsList: Array<ProductsByBrand.AsObject>,
  }
}

export class ListCurrentOrderListRequest extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): ListCurrentOrderListRequest.AsObject;
  static toObject(includeInstance: boolean, msg: ListCurrentOrderListRequest): ListCurrentOrderListRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: ListCurrentOrderListRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): ListCurrentOrderListRequest;
  static deserializeBinaryFromReader(message: ListCurrentOrderListRequest, reader: jspb.BinaryReader): ListCurrentOrderListRequest;
}

export namespace ListCurrentOrderListRequest {
  export type AsObject = {
  }
}

export class ListCurrentOrderListResponse extends jspb.Message {
  clearProductbrandsList(): void;
  getProductbrandsList(): Array<ProductsByBrand>;
  setProductbrandsList(value: Array<ProductsByBrand>): void;
  addProductbrands(value?: ProductsByBrand, index?: number): ProductsByBrand;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): ListCurrentOrderListResponse.AsObject;
  static toObject(includeInstance: boolean, msg: ListCurrentOrderListResponse): ListCurrentOrderListResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: ListCurrentOrderListResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): ListCurrentOrderListResponse;
  static deserializeBinaryFromReader(message: ListCurrentOrderListResponse, reader: jspb.BinaryReader): ListCurrentOrderListResponse;
}

export namespace ListCurrentOrderListResponse {
  export type AsObject = {
    productbrandsList: Array<ProductsByBrand.AsObject>,
  }
}

export class GetBrandsRequest extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): GetBrandsRequest.AsObject;
  static toObject(includeInstance: boolean, msg: GetBrandsRequest): GetBrandsRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: GetBrandsRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): GetBrandsRequest;
  static deserializeBinaryFromReader(message: GetBrandsRequest, reader: jspb.BinaryReader): GetBrandsRequest;
}

export namespace GetBrandsRequest {
  export type AsObject = {
  }
}

export class GetBrandsResponse extends jspb.Message {
  clearBrandsList(): void;
  getBrandsList(): Array<Brand>;
  setBrandsList(value: Array<Brand>): void;
  addBrands(value?: Brand, index?: number): Brand;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): GetBrandsResponse.AsObject;
  static toObject(includeInstance: boolean, msg: GetBrandsResponse): GetBrandsResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: GetBrandsResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): GetBrandsResponse;
  static deserializeBinaryFromReader(message: GetBrandsResponse, reader: jspb.BinaryReader): GetBrandsResponse;
}

export namespace GetBrandsResponse {
  export type AsObject = {
    brandsList: Array<Brand.AsObject>,
  }
}

export class QueryProductsRequest extends jspb.Message {
  getQuery(): string;
  setQuery(value: string): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): QueryProductsRequest.AsObject;
  static toObject(includeInstance: boolean, msg: QueryProductsRequest): QueryProductsRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: QueryProductsRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): QueryProductsRequest;
  static deserializeBinaryFromReader(message: QueryProductsRequest, reader: jspb.BinaryReader): QueryProductsRequest;
}

export namespace QueryProductsRequest {
  export type AsObject = {
    query: string,
  }
}

export class QueryProductsResponse extends jspb.Message {
  clearResultsList(): void;
  getResultsList(): Array<Product>;
  setResultsList(value: Array<Product>): void;
  addResults(value?: Product, index?: number): Product;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): QueryProductsResponse.AsObject;
  static toObject(includeInstance: boolean, msg: QueryProductsResponse): QueryProductsResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: QueryProductsResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): QueryProductsResponse;
  static deserializeBinaryFromReader(message: QueryProductsResponse, reader: jspb.BinaryReader): QueryProductsResponse;
}

export namespace QueryProductsResponse {
  export type AsObject = {
    resultsList: Array<Product.AsObject>,
  }
}

export class CompleteCartRequest extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): CompleteCartRequest.AsObject;
  static toObject(includeInstance: boolean, msg: CompleteCartRequest): CompleteCartRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: CompleteCartRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): CompleteCartRequest;
  static deserializeBinaryFromReader(message: CompleteCartRequest, reader: jspb.BinaryReader): CompleteCartRequest;
}

export namespace CompleteCartRequest {
  export type AsObject = {
  }
}

export class CompleteCartResponse extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): CompleteCartResponse.AsObject;
  static toObject(includeInstance: boolean, msg: CompleteCartResponse): CompleteCartResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: CompleteCartResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): CompleteCartResponse;
  static deserializeBinaryFromReader(message: CompleteCartResponse, reader: jspb.BinaryReader): CompleteCartResponse;
}

export namespace CompleteCartResponse {
  export type AsObject = {
  }
}

export class CompleteOrderListRequest extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): CompleteOrderListRequest.AsObject;
  static toObject(includeInstance: boolean, msg: CompleteOrderListRequest): CompleteOrderListRequest.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: CompleteOrderListRequest, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): CompleteOrderListRequest;
  static deserializeBinaryFromReader(message: CompleteOrderListRequest, reader: jspb.BinaryReader): CompleteOrderListRequest;
}

export namespace CompleteOrderListRequest {
  export type AsObject = {
  }
}

export class CompleteOrderListResponse extends jspb.Message {
  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): CompleteOrderListResponse.AsObject;
  static toObject(includeInstance: boolean, msg: CompleteOrderListResponse): CompleteOrderListResponse.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: CompleteOrderListResponse, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): CompleteOrderListResponse;
  static deserializeBinaryFromReader(message: CompleteOrderListResponse, reader: jspb.BinaryReader): CompleteOrderListResponse;
}

export namespace CompleteOrderListResponse {
  export type AsObject = {
  }
}

export class Brand extends jspb.Message {
  getId(): number;
  setId(value: number): void;

  getCode(): string;
  setCode(value: string): void;

  getName(): string;
  setName(value: string): void;

  getIncluded(): boolean;
  setIncluded(value: boolean): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): Brand.AsObject;
  static toObject(includeInstance: boolean, msg: Brand): Brand.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: Brand, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): Brand;
  static deserializeBinaryFromReader(message: Brand, reader: jspb.BinaryReader): Brand;
}

export namespace Brand {
  export type AsObject = {
    id: number,
    code: string,
    name: string,
    included: boolean,
  }
}

export class Product extends jspb.Message {
  getId(): number;
  setId(value: number): void;

  getSku(): string;
  setSku(value: string): void;

  getSalesname(): string;
  setSalesname(value: string): void;

  getSuppliername(): string;
  setSuppliername(value: string): void;

  getBrandcode(): string;
  setBrandcode(value: string): void;

  getLatestprice(): number;
  setLatestprice(value: number): void;

  getLateststock(): number;
  setLateststock(value: number): void;

  getBarcode(): string;
  setBarcode(value: string): void;

  getThumbnailurl(): string;
  setThumbnailurl(value: string): void;

  getBrandname(): string;
  setBrandname(value: string): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): Product.AsObject;
  static toObject(includeInstance: boolean, msg: Product): Product.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: Product, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): Product;
  static deserializeBinaryFromReader(message: Product, reader: jspb.BinaryReader): Product;
}

export namespace Product {
  export type AsObject = {
    id: number,
    sku: string,
    salesname: string,
    suppliername: string,
    brandcode: string,
    latestprice: number,
    lateststock: number,
    barcode: string,
    thumbnailurl: string,
    brandname: string,
  }
}

export class ProductsByBrand extends jspb.Message {
  getBrandname(): string;
  setBrandname(value: string): void;

  clearProductquantitiesList(): void;
  getProductquantitiesList(): Array<ProductQuantity>;
  setProductquantitiesList(value: Array<ProductQuantity>): void;
  addProductquantities(value?: ProductQuantity, index?: number): ProductQuantity;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): ProductsByBrand.AsObject;
  static toObject(includeInstance: boolean, msg: ProductsByBrand): ProductsByBrand.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: ProductsByBrand, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): ProductsByBrand;
  static deserializeBinaryFromReader(message: ProductsByBrand, reader: jspb.BinaryReader): ProductsByBrand;
}

export namespace ProductsByBrand {
  export type AsObject = {
    brandname: string,
    productquantitiesList: Array<ProductQuantity.AsObject>,
  }
}

export class ProductQuantity extends jspb.Message {
  hasProduct(): boolean;
  clearProduct(): void;
  getProduct(): Product | undefined;
  setProduct(value?: Product): void;

  getQuantity(): number;
  setQuantity(value: number): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): ProductQuantity.AsObject;
  static toObject(includeInstance: boolean, msg: ProductQuantity): ProductQuantity.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: ProductQuantity, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): ProductQuantity;
  static deserializeBinaryFromReader(message: ProductQuantity, reader: jspb.BinaryReader): ProductQuantity;
}

export namespace ProductQuantity {
  export type AsObject = {
    product?: Product.AsObject,
    quantity: number,
  }
}

export class Paging extends jspb.Message {
  getTotalresults(): number;
  setTotalresults(value: number): void;

  getLast(): number;
  setLast(value: number): void;

  serializeBinary(): Uint8Array;
  toObject(includeInstance?: boolean): Paging.AsObject;
  static toObject(includeInstance: boolean, msg: Paging): Paging.AsObject;
  static extensions: {[key: number]: jspb.ExtensionFieldInfo<jspb.Message>};
  static extensionsBinary: {[key: number]: jspb.ExtensionFieldBinaryInfo<jspb.Message>};
  static serializeBinaryToWriter(message: Paging, writer: jspb.BinaryWriter): void;
  static deserializeBinary(bytes: Uint8Array): Paging;
  static deserializeBinaryFromReader(message: Paging, reader: jspb.BinaryReader): Paging;
}

export namespace Paging {
  export type AsObject = {
    totalresults: number,
    last: number,
  }
}

