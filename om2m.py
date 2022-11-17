from onem2m_func import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae1 = "FSR"
cnt1 = "node1"
ae2 = "Number_Of_Steps"
cnt2 = "node1"
ae3 = "EMG"
cnt3 = "node1"

create_ae(uri_cse, ae1)
create_ae(uri_cse, ae2)
create_ae(uri_cse, ae3)

uri_ae1 = uri_cse + "/" + ae1
create_cnt(uri_ae1, cnt1)
uri_ae2 = uri_cse + "/" + ae2
create_cnt(uri_ae2, cnt2)
uri_ae3 = uri_cse + "/" + ae3
create_cnt(uri_ae3, cnt3)

uri_cnt1 = uri_ae1 + "/" + cnt1
create_data_cin(uri_cnt1, "ESW FSR")
uri_cnt2 = uri_ae2 + "/" + cnt2
create_data_cin(uri_cnt2, "ESW FSR")
uri_cnt3 = uri_ae3 + "/" + cnt3
create_data_cin(uri_cnt3, "ESW FSR")
