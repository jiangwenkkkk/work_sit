 CREATE TABLE `rm_qdcx_5g`(
  `type` int,
  `msimdn` string,
  `imsi` string,
  `imei` string,
  `p_gw` string,
  `apnni` string,
  `charging_id` string,
  `local_seq` string,
  `record_seq` string,
  `pdp_addr` string,
  `ims` string,
  `termination` int,
  `home_code` string,
  `visit_code` string,
  `rgfourg` string,
  `rat_type` string,
  `epcf_ip` string,
  `rgfiveg` string,
  `report_time` string,
  `reserver2` bigint,
  `reserver3` bigint,
  `sr_st` string,
  `roam_st` string,
  `flag_ot` int,
  `file_name` string,
  `timeoffirst` string,
  `timeoflast` string
)
PARTITIONED BY (
  `date_no` string,
  `provinceid` string)
ROW FORMAT DELIMITED
  FIELDS TERMINATED BY '^'
STORED AS textfile;